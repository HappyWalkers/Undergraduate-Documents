import java.util.*;

/**
 * @author 7zq12lvm
 * @create 2020-05-13 16:42
 */

public class Banker {

    static Random random = new Random();
    static Scanner scanner = new Scanner(System.in);
    static int processNum = 5;//设定进程数量
    static int resourceTypesNum = 5; //设定资源种类数
    static int resourceAvailableQuantityStart = 7;
    static int resourceAvailableQuantityEnd = 10; //设定初始化系统拥有每种资源的数量范围
    static int maxNeedPerResource = 4; //设定每个进程最多需求每种资源的数量
    static List<Integer> available = new ArrayList<>();
    static List<ArrayList<Integer>> need = new ArrayList<>();
    static List<ArrayList<Integer>> allocation = new ArrayList<>();
    static List<ArrayList<Integer>> maxNeed = new ArrayList<>();
    static int reqProcessId;
    static ArrayList<Integer> reqVector;
    static boolean isApply;

    public static void main(String[] args) {
        System.out.println("-------------------------------------------------");
        System.out.println("-                                               -");
        System.out.println("-              银行家算法演示                     -");
        System.out.println("-              @物联网1802白明强                  -");
        System.out.println("-                                               -");
        System.out.println("-------------------------------------------------");


        init();//初始化各类资源

        printStatus();

        while(true){
            input();
            if(isApply){
                handleAllocation();
            }else{
                releaseResource();
            }

            System.out.println("---------------------------------------------");
            printStatus();
            System.out.println("---------------------------------------------");
        }
    }

    public static void handleAllocation() {
        if(!checkAboveEqualZero(doMathForList('-',need.get(reqProcessId),reqVector))
        ||!checkAboveEqualZero(doMathForList('-',available,reqVector))){
            System.out.println("错误！您所申请的资源数目超过了该进程宣称需要的最大值！");
        }else{
            ArrayList<Integer> newAvaliable;
            ArrayList<ArrayList<Integer>> newAllocation = new ArrayList<>(allocation);
            ArrayList<ArrayList<Integer>> newNeed = new ArrayList<>(need);

            newAvaliable = doMathForList('-',available, reqVector);
            newAllocation.set(reqProcessId,doMathForList('+',allocation.get(reqProcessId),reqVector));
            newNeed.set(reqProcessId,doMathForList('-',need.get(reqProcessId),reqVector));

            if(isSafe(newAvaliable,newAllocation,newNeed)){
                available = doMathForList('-',available, reqVector);
                allocation.set(reqProcessId,doMathForList('+',allocation.get(reqProcessId),reqVector));
                need = newNeed;
                System.out.println("分配资源成功！");
            }else{
                System.out.println("分配资源失败！");
            }
        }
    }

    public static boolean isSafe(ArrayList<Integer> newAvailable,ArrayList<ArrayList<Integer>> newAllocation,ArrayList<ArrayList<Integer>> newNeed) {
        ArrayList<Integer> work = new ArrayList<>(newAvailable);

            ArrayList<Integer> safe = new ArrayList<>();


        for (int i = 0; i < processNum; i++) {
            boolean contains = safe.contains(i);
            boolean canAlloc = checkAboveEqualZero(doMathForList('-',  work,newNeed.get(i)));
            if (!contains && canAlloc) {
                safe.add(i);
                work = doMathForList('+', work, newAllocation.get(i));
                i = -1;
            } else {
                if (safe.size() == processNum) {
                    System.out.println("安全序列为：");
                    System.out.println(safe);
                    return true;
                }
            }

        }
        System.out.println("会进入不安全状态！分配失败！");
        return false;

    }

    public static void releaseResource() {
        available = doMathForList('+',available,reqVector);
        allocation.set(reqProcessId,doMathForList('-',allocation.get(reqProcessId),reqVector));
        need.set(reqProcessId,doMathForList('+',need.get(reqProcessId),reqVector));
    }

    public static ArrayList<Integer> doMathForList(char type,List<Integer> first,List<Integer> second){
        ArrayList<Integer> result = new ArrayList<>();
        if(type == '+'){
            for (int i = 0; i < resourceTypesNum ; i++) {
                result.add(first.get(i)+second.get(i));
            }
        }
        if(type == '-') {
            for (int i = 0; i < resourceTypesNum; i++) {
                result.add(first.get(i) - second.get(i));
            }
        }
        return result;
    }

    public static boolean checkAboveEqualZero(List<Integer> l){ //检查数组的一行是否全部大于0
        for (Integer integer : l) {
            if(integer<0){
                return false;
            }
        }
        return true;
    }


    public static void init(){
        //系统资源数量available
        random.ints(resourceTypesNum,resourceAvailableQuantityStart,resourceAvailableQuantityEnd).forEach(available::add);
        //生成进程需求矩阵maxNeed
        for (int i = 0; i < processNum ; i++) {
            ArrayList<Integer> temp = new ArrayList<>();
            for (int j = 0; j < resourceTypesNum; j++) {
                temp.add(random.nextInt(maxNeedPerResource)+3);
            }
            maxNeed.add(temp);
        }

        //生成need矩阵，保存当前状态下进程需要的资源数量，初始化为maxNeed
        for (int i = 0; i < processNum ; i++) {
            need.add(new ArrayList<>());
            for (int j = 0; j < resourceTypesNum ; j++) {
                need.get(i).add(maxNeed.get(i).get(j));
            }
        }//深拷贝

        //已经分配的资源数量
        for (int i = 0; i < processNum; i++) {
            ArrayList<Integer> temp = new ArrayList<>();
            for (int j = 0; j < resourceTypesNum; j++) {
                temp.add(0);
            }
            allocation.add(temp);
        }
    }

    public static void input(){

        System.out.println("您申请资源(1)还是释放资源(2)？");
        int choice=scanner.nextInt();
        if(choice==1){
            isApply=true;
            System.out.println("请输入准备申请资源的进程编号：");
            reqProcessId = scanner.nextInt();//请求资源的进程编号

            System.out.println("请输入该进程申请的资源数量(以空格分隔，按回车结束)：");
            reqVector = new ArrayList<>();
            for (int i = 0; i < resourceTypesNum; i++) {
                reqVector.add(scanner.nextInt());
            }
        }else if(choice==2){
            isApply=false;
            System.out.println("请输入准备释放资源的进程编号：");
            reqProcessId = scanner.nextInt();//释放资源的进程编号

            System.out.println("请输入该进程释放的资源数量(以空格分隔，按回车结束)：");
            reqVector = new ArrayList<>();

            for (int i = 0; i < resourceTypesNum; i++) {
                reqVector.add(scanner.nextInt());
            }

        }else{
            System.out.println("输入有误，请重新输入！");
            input();
        }

    }

    public static void printStatus(){
        System.out.print("maxNeed:");
        System.out.println(maxNeed);

        System.out.print("available:");
        System.out.println(available);
        System.out.print("allocation:");
        System.out.println(allocation);
        System.out.print("need:");
        System.out.println(need);
    }

}

