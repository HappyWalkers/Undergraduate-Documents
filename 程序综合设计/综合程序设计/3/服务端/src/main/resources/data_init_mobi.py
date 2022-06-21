import pymysql as MySQLdb
import os
import uuid

PWD = "C:\Projects\IdeaProjects\KindlePush\src\main\\resources\\tmp\\"
MYSQL_USERNAME = "root"




db = MySQLdb.connect(host="127.0.0.1",user="root",password="tsinghuabmq123",database="kindlepushv2",charset="utf8")
cursor = db.cursor()
def save2Database(info):
    #需要字典
    try:
        # sql = """insert into kindlepushv2.bookinfo(bookname,author,description,date,covername)\
        #   value (%s,%s,%s,%s,%s);"""
        sql = "insert into kindlepushv2.bookinfo(bookname,author,description,date,path,covername) value "+ \
              "("+ \
              "\'"+db.escape_string(info["title"])+"\'"+","+ \
              "\'"+db.escape_string(info["author"])+"\'"+","+ \
              "\'"+db.escape_string(info["description"])+"\'" +","+ \
              "\'"+db.escape_string(info["date"])+"\'"+","+ \
              "\'"+db.escape_string(info["path"])+"\'"+","+ \
              "\'"+db.escape_string(info["covername"])+"\'"+");"
        # cursor.execute(sql%(info["title"],info["author"],info["description"],info["date"],info["covername"]))
        cursor.execute(sql)
        db.commit()
    except Exception as e:
        print(e)
        print(info["title"]+" failed to save")


files = os.listdir(PWD)
for file in files:
    path = PWD + file
    #使用ebooklib读取元信息
    try:
        ebook = epub.read_epub(path)
        title = ebook.title
    except:
        continue
    try:
        author = ebook.get_metadata("DC","creator")[0][0]
    except:
        author = "Unknown"
    try:
        description = ebook.get_metadata("DC","description")[0][0]
    except:
        description = "Unknown"
    try:
        date = ebook.get_metadata("DC","date")[0][0]
    except:
        date = "Unknown"

    try:
        covername = ebook.get_metadata("OPF","cover")[0][1]["content"]
        imageObject = ebook.get_item_with_id(covername)
        imageBytes = imageObject.content
        imageFilename = str(uuid.uuid1())
        with open(IMAGE_SAVE_DIR+imageFilename+'.jpg',"wb+") as f:
            f.write(imageBytes)
    except Exception as e:
        print(e)
        print("error happened when creating cover file")
    info = {"title":title,"author":author,"description":description,"date":date,"covername":imageFilename,"path":path}
    save2Database(info)

cursor.close()
db.close()

