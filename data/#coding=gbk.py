import os
import sys
def rename():
    path=input("请输入路径(例如D:\\\\picture)：")
    name=input("请输入开头名:")
    startNumber=input("请输入开始数:")
    fileType=input("请输入后缀名（如 .jpg、.txt等等）:")
    print("正在生成以"+name+startNumber+fileType+"迭代的文件名")
    count=0
    filelist=os.listdir(path)
    for files in filelist:
        Olddir=os.path.join(path,files)
        if os.path.isdir(Olddir):
            continue
        Newdir=os.path.join(path,name+str(count+int(startNumber))+fileType)
        os.rename(Olddir,Newdir)
        count+=1
    print("一共修改了"+str(count)+"个文件")

rename() 