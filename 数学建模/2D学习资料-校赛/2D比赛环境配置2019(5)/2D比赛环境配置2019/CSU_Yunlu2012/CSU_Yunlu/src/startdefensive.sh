#!/bin/sh

DIR=`dirname $0`

player="${DIR}/csu_player"
coach="${DIR}/csu_coach"
teamname="csuyunlu"
host="localhost"

config="${DIR}/player.conf"
config_dir="${DIR}/formations-dt"

coach_config="${DIR}/coach.conf"

number=8
usecoach="true"

sleepprog=sleep
goaliesleep=1
sleeptime=0

usage()
{
  (echo "Usage: $0 [options]"
   echo "Possible options are:"
   echo "      --help                print this"
   echo "  -h, --host HOST           specifies server host") 1>&2
}

while [ $# -gt 0 ]
	do
	case $1 in

    --help)
      usage
      exit 0
      ;;

    -h|--host)
      if [ $# -lt 2 ]; then
        usage
        exit 1
      fi
      host=$2
      shift 1
      ;;

    *)
      usage
      exit 1
      ;;
  esac

  shift 1
done

opt="--player-config ${config} --config_dir ${config_dir}"
opt="${opt} -h ${host} -t ${teamname}"

if [ $number -gt 0 ]; then
  $player ${opt} -g &
  $sleepprog $goaliesleep
fi

i=2
while [ $i -le ${number} ] ; do
  $player ${opt} &
  $sleepprog $sleeptime
  i=`expr $i + 1`
done

coachopt="--coach-config ${coach_config}"
coachopt="${coachopt} -h ${host} -t ${teamname}"
coachopt="${coachopt} ${coachdebug}"
$coach ${coachopt} &

