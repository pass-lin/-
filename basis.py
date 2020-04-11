# -*- coding: utf-8 -*-
"""
Created on Mon Apr  6 21:29:57 2020

@author: Administrato"""
import pandas as pd
import numpy as np
import random as random
import matplotlib.pyplot as plt
def mapping(a,m):#大于这个数则返回1，小于返回0
        return 1 if a>=m else 0
def loadfile(filename,n=100):
    m=pd.read_csv(filename)#读取文件默认读取前n行
    return m[:n]
def distance(dataset,testline,n=1):
    dataset=np.array(dataset)
    testline=np.array(testline)
    return np.sum((dataset-testline)**2,axis=n)**0.5#

def twodivide(m1,m2):
    n1=np.median(m1,axis=0)
    n2=np.median(m2,axis=0)
    n=(n1+n2)/2#算的两个数据的中位数并取其平均数
    vfunc=np.vectorize(mapping)#将函数向量化
    for i in range(m1.shape[1]):
        m1[:,i]=vfunc(m1[:,i],n[i])
        m2[:,i]=vfunc(m2[:,i],n[i])
    return m1,m2
def delenan(data,dic=0):#删除缺失值
    return data.dropna()
def fillyourself(data,dic=0): #用字典或常数自定义输入值 
    return data.fillna(dic)
def fillmeans(data,dic=0):#填充平均值
    return data.fillna(data.mean())
def nanoprate(data,operate=delenan,dic=0):#传入的是一个dataframe格式的数据          
    return operate(data,dic)
class pretreatment():
    def __int__(self):
        return 0
    def onehot(self,datamat,index):#以index进行独热编码,index是一个列表
        return pd.get_dummies(datamat,prefix=index)
    def standardization(self,datamat):#标准差标准化
        u=np.mean(datamat,axis=0)
        std=np.std(datamat, axis=0)
        return (datamat-u)/std     
    def nanoperate(self,data,operate=delenan,dic=0):#传入的是一个dataframe格式的数据          
        return operate(data,dic)
    def Discretization(self,data,index,n=4):
    #输入一个dataframe，标签index和划分箱子数n
        data[index]=pd.cut(data[index],n)
        return data
    def threesigma(self,data,index):
    #传入一个dataframe数据，根据3∂原则处理异常值
        m=np.mean(data[index])
        n=m*3
        returnmat=data[abs(data[index]-m)<n]
        return returnmat
    def Tukeytest(self,data,index):#箱式法则
     #以index作为标准进行运算
        Percentile = np.percentile(data[index],[0,25,50,75,100])
     #求各个百分比代表的数
        IQR = Percentile[3] - Percentile[1]
        UpLimit = abs(Percentile[3]+IQR*1.5)
        DownLimit = abs(Percentile[1]-IQR*1.5)
     #分别求上下边界
        returnmat_1=data[data[index]>=Percentile[2]]
        returnmat_1=returnmat_1[returnmat_1[index]-Percentile[2]<=UpLimit]
        returnmat_2=data[data[index]<Percentile[2]]
        returnmat_2=returnmat_2[Percentile[2]-returnmat_2[index]<=DownLimit]
     #符合条件的代入
        return pd.concat([returnmat_1,returnmat_2])
 

    def similarity(self,data1,data2):
        #传入两个array
        m1=data1.copy()#传入两个array
        m2=data2.copy()
        twodivide(m1,m2)
        r=np.zeros(m1.shape[1])#创建两个零矩阵
        s=np.zeros(m1.shape[1])
        for i in range(m1.shape[1]):
            for j in range(m1.shape[0]):
                if m1[j,i]==0 and m2[j,i]==1:
                    s[i]+=1#记录data1中为1data2中为0的数量
                if m2[j,i]==0 and m1[j,i]==1:
                    r[i]+=1#记录data2中为1data1中为0的数量
        g=(r+s)/m1.shape[0]#计算相异性 
        g=1-g#计算相似性
        return g
    def autoNorm(self,dataset):#标准归一化数据
        minvalue=dataset.min(0)#取出每一列的最大值和最小值
        maxvalue=dataset.max(0)
        numrange=maxvalue-minvalue
        newdata=np.zeros(np.shape(dataset))#生成一个与dataset相同尺寸的数组
        newdata=newdata+dataset
        return (newdata-minvalue)/numrange#根据计算公式返回
def ROC(truedata,forecastdata,threshold,twodivid):
    tpfn=sum(truedata)#计算正例数
    fptn=np.shape(truedata)[0]-tpfn#计算负例数
    m=np.argsort(-forecastdata)#升序排序
    forecastdata=forecastdata.copy()[m]
    truedata=truedata.copy()[m]
    tpr=1/tpfn#y轴走得单位距离
    fpr=1/fptn#x轴走得单位距离
    x=0
    y=0
    xarray=[]#存储绘图用的xy点
    yarray=[]
    for i in range(np.shape(truedata)[0]):
        if truedata[i]==1:
            y+=tpr#如果当前点是正例，则y走一单位距离
        else:
            x+=fpr#否则x走一单位距离
        xarray.append(x)
        yarray.append(y)
    plt.plot(xarray,yarray,linestyle='--',marker='x')#绘图
    for i in range(np.shape(truedata)[0]):
         plt.text(xarray[i],yarray[i],s=forecastdata[i])
def AUC(truedata,forecastdata,threshold,twodivid):
    tpfn=sum(truedata)#计算正例数
    fptn=np.shape(truedata)[0]-tpfn#计算负例数
    m=np.argsort(-forecastdata)#升序排序
    forecastdata=forecastdata.copy()[m]
    truedata=truedata.copy()[m]
    tpr=1/tpfn#y轴走得单位距离
    fpr=1/fptn#x轴走得单位距离
    x=0
    y=0
    xarray=[]#存储绘图用的xy点
    yarray=[]
    for i in range(np.shape(truedata)[0]):
        if truedata[i]==1:
            y+=tpr#如果当前点是正例，则y走一单位距离
        else:
            x+=fpr#否则x走一单位距离
        xarray.append(x)
        yarray.append(y)
    auc=0
    for i in range(0,np.shape(truedata)[0]-1):#根据AUC计算公式计算
        auc+=(xarray[i+1]-xarray[i])*(yarray[i]+yarray[i+1])
    auc=auc/2
    return auc

def accuracy(truedata,forecastdata,threshold=0.5,twodivid=1):#准确值
    #接口为真实值，预测值，阈值，和是否为二分类的预测数据
    if twodivid!=1:#如果不是二分类预测的数据，那么比较预测结果
        m=np.shape(truedata)[0]
        n=0        
        for i in range(m):
            n=n+int(truedata[i]==forecastdata[i])
        return n/m
    else:#如果是先进行二分的处理
        forecast=forecastdata.copy()
        forecast[forecast<threshold]=0
        forecast[forecast>=threshold]=1#某点概率为正大于等于阈值则为1，反之为0
        m=np.shape(truedata)[0]
        n=0
        for i in range(m):#随后进行比较
            n=n+int(truedata[i]==forecast[i])
        return n/m
def precision(truedata,forecastdata,threshold=0.5,twodivid=1):
    forecast=forecastdata.copy()#二分的处理
    forecast[forecast<threshold]=0
    forecast[forecast>=threshold]=1#某点概率为正大于等于阈值则为1，反之为0
    r=np.shape(truedata)[0]
    m=np.sum(forecast)#得到预测为正的数量
    n=0            
    for i in range(r):#随后进行比较
        n=n+int(truedata[i]==forecast[i]==1)#正确预测为正的加一
    return n/m
def recall(truedata,forecastdata,threshold=0.5,twodivid=1):
    forecast=forecastdata.copy()#二分的处理
    forecast[forecast<threshold]=0
    forecast[forecast>=threshold]=1#某点概率为正大于等于阈值则为1，反之为0
    r=np.shape(truedata)[0]
    m=np.sum(truedata)#得到真正为正的数量
    n=0            
    for i in range(r):#随后进行比较
        n=n+int(truedata[i]==forecast[i]==1)#正确预测为正的加一
    return n/m
def Fscore(truedata,forecastdata,threshold=0.5,twodivid=1):
    m=np.float(recall(truedata,forecastdata))
    n=np.float(precision(truedata,forecastdata))        
    return 1/m+1/n
def PR(truedata,forecastdata,threshold=0.5,twodivid=1):
    m=np.argsort(-forecastdata)#升序排序
    forecast=forecastdata.copy()[m]
    true=truedata.copy()[m]
    
    xarray=[]#存储绘图用的xy点
    yarray=[]
    for i in range(np.shape(truedata)[0]):
        if i==0:#第一个点应该是（0，1）
            xarray.append(0)
            yarray.append(1)
        else:#以当前值为阈值计算召回率和精确率
            xarray.append(recall(true,forecast,forecast[i]))
            yarray.append(precision(true,forecast,forecast[i]))  
    plt.plot(xarray,yarray,linestyle='--',marker='x')#绘图
def Variance(truedata,forecastdata):#方差
    m=np.mean(forecastdata,axis=0)
    return np.sum(np.power(m-forecastdata,2)/len(forecastdata))
def Bias(truedata,forecastdata):#偏差
    return np.sum(np.power(truedata-forecastdata,2)/len(truedata))
def MSE(truedata,forecastdata):
    return np.sum(np.power(truedata-forecastdata,2)/len(truedata))
def RMSE(truedata,forecastdata):
    m=np.sum(np.power(truedata-forecastdata,2)/len(truedata))
    return m**0.5
def MAE(truedata,forecastdata):
    m=abs(truedata-forecastdata)
    return np.sum(m)/len(truedata)
def MAPE(truedata,forecastdata):
    m=abs(truedata-forecastdata)/abs(truedata)
    return str(np.sum(m)/len(truedata)*100)+'%'
def rpower(truedata,forecastdata):#R平方
    m=np.mean(truedata,axis=0)
    ssr=np.power(truedata-forecastdata,2)
    sst=np.power(truedata-m,2)
    r2=np.sum(ssr)/np.sum(sst)
    return 1-r2
def holdout(data,k=0.3):
    ###传入一个array数据进行留出法划分数据集
    test=data.copy()
    n=test.shape[0]#获取数据集的形状
    R=range(0,n)
    r=random.sample(R,int(k*n))#生成一个随机数列表作为测试集的索引
    m=[]
    for i in R:#如果数i在测试集中，则不在训练集中
        if i not in r:
            m.append(i)
    train=test[r]#获得测试集
    test=test[m]#获得训练集
    return test,train
def bootstrapping(data,alpha=1):#自助法
    n=data.shape[0]#获取数据集的形状
    test=data.copy()
    m=range(0,n)
    R=set(m)
    k=pd.DataFrame(R)
    g=k.sample(n=n,replace=True)#随机抽取n个样本
    g=list(g.loc[:,0])
    d=set(g)#产生一个被抽取过的序列集合
    train=test[g]#训练集
    test=test[list(R.difference(d))]#测试集为未被抽取过得
    return test,train    
class knnchat():
    def __int__(self):
        return 0
    def knn(self,dataset,label,inx,k):
    #输入向量inx，训练向量dataset，前k个值，对应标签label
        dist=distance(dataset,inx)#计算距离
        sortlabel=dist.argsort()#排序取前k个
        beforek={}#定义一个字典
        for i in range(k):#统计前k个距离各自标签的数量
            beforek[label[sortlabel[i]]]=beforek.get(label[sortlabel[i]],0)+1
        returnvalue=sorted(beforek.items(),key=lambda item: item[1],reverse=True)
    #以键值进行排序
        return int(returnvalue[0][0])#返回预测值 
    def loaddata(self,filename,n=1000,m=1):
        a=pd.read_csv(filename)#读取文件默认读取前n行第m列起
        a=a.values       
        return a[:n,m:]
    def test(self,datatmat,k=10,divide=holdout,judge=accuracy,n=0.05):
        #传入测试数据集，重复测试次数k，划分方法和判断方法
        #测试数据集最后一列为结果y值
        #n为划分数据集的比例
        g=knnchat()
        num=0
        for i in range(k):
            test,train=divide(datatmat,n)#划分训练集和测试集
            fre=[]
            for i in range(test.shape[0]):#把测试集逐个进行运算
                fre.append(g.knn(train[:,:-1],train[:,-1],test[i,:-1],20))
            fre=np.array(fre)           
            num+=judge(test[:,-1],fre,0.5,2)#计算精确值
        return num/k#返回平均值
    def crosstest(self,datamat,k=10,divide=holdout,judge=accuracy,n=0.05):
        m=np.shape(datamat)[0]
        R=set(range(m))#建立一个全部索引的集合
        klist=[]
        g=knnchat()
        for i in range(k):
            temp=random.sample(R,int(len(R)/(k-i)))#随机取出总集合的1/k
            R=R.difference(temp)#总集合中删除添加的那部分
            klist.append(np.array(temp))#将新生成的数据加入klist
        R=set(range(m))#重新生成总集合
        num=0
        for i in range(k):
            test=datamat[klist[i]]#逐步取第k份为测试集
            t=list(R.difference(klist[i]))#其余部分为训练集合
            train=datamat[t]
            fre=[]
            for i in range(test.shape[0]):#把测试集逐个进行运算
                fre.append(g.knn(train[:,:-1],train[:,-1],test[i,:-1],20))
            fre=np.array(fre)           
            num+=judge(test[:,-1],fre,0.5,2)#计算精确值
        return num/k#返回平均值
class standreger():
    def __int__(self):
        self.ws=0
        return 0
    def standregerr(self,datamat):
        xarry=datamat[:,:-1]
        yarry=datamat[:,-1]#y为m的最后一列
        xmat=np.mat(xarry)#xy矩阵化
        ymat=np.mat(yarry).T
        xtx=xmat.T*xmat
        if np.linalg.det(xtx)==0:#行列式为零则报错
            return 0
        ws=xtx.I*xmat.T*ymat
        self.ws=ws
        return ws#返回关键值
    def test(self,datatmat,k=10,divide=holdout,judge=rpower):
        #传入测试数据集，重复测试次数k，划分方法和判断方法
        #测试数据集最后一列为结果y值
        s=standreger()
        num=0
        g=0
        for i in range(k):
            test,train=divide(datatmat)#划分训练集和测试集
            w=s.standregerr(train)
            if np.sum(w)!=0:#进行运算和评估
                precast=np.mat(test[:,:-1])*w
                precast=precast.T
                num+=judge(test[:,-1],precast)
                g+=1#记录有效运算的次数
        return num/g#返回平均值
    def loaddata(self,filename,n=100,m=1):
        a=pd.read_csv(filename)
        #读取文件默认读取前n行,从第m列开始读
        d,b=np.shape(a)
        a=a.values
        k=np.ones((d-(m-1),b))#建立一个axb全为一的矩阵
        k[:,m:]=a[:,m:]#x0列为一，其余为m的n-1列
        return k[:n,m:]    
    def crosstest(self,datamat,k=10,divide=holdout,judge=rpower):
        m=np.shape(datamat)[0]
        R=set(range(m))#建立一个全部索引的集合
        klist=[]
        for i in range(k):
            temp=random.sample(R,int(len(R)/(k-i)))#随机取出总集合的1/k
            R=R.difference(temp)#总集合中删除添加的那部分
            klist.append(np.array(temp))#将新生成的数据加入klist
        R=set(range(m))#重新生成总集合
        num=0
        s=standreger()
        g=0
        for i in range(k):
            test=datamat[klist[i]]#逐步取第k份为测试集
            t=list(R.difference(klist[i]))#其余部分为训练集合
            train=datamat[t]
            w=s.standregerr(train)
            if np.sum(w)!=0:#进行运算和评估
                precast=np.mat(test[:,:-1])*w
                precast=precast.T
                num+=judge(test[:,-1],precast)
                g+=1#记录有效运算的次数
        return num/g#返回平均值
    def draw(self,datamat,w,x=1):
        #绘图函数，加入用数据的第x个特征作为x轴
        #其中datamat应为测试集。且datamat的最后一列应该为数据的标签
        yarry=datamat[:,-1]
        xarry=datamat[:,:-1]
        ymat=np.mat(xarry)*w
        plt.scatter(xarry[:,x],yarry)
        plt.plot(xarry[:,x],ymat)     
def randCent(dataset,k):
    n=np.shape(dataset)[1]
    minvalue=dataset.min(0)#取出每一列的最大值和最小值
    maxvalue=dataset.max(0)
    numrange=maxvalue-minvalue
    returnmat=np.zeros((k,n))#生成的随机矩阵范围要在最大值与最小值之间
    rand=np.random.random((k,n))
    returnmat=returnmat+minvalue+rand*numrange
    return returnmat
class k_means():
    def __int__(self,filename):
        self.filename=filename
    def kmeans(self,dataset,k=5,dist=distance,createCent=randCent):
        flag=1#是否继续迭代的标志
        m=np.shape(dataset)[0]#获得形状
        returnmat=np.mat(np.zeros((2,m)))#生成一个记录矩阵
        centroids=randCent(dataset,k)#生成k个随机簇
        dataset=np.mat(dataset)#矩阵化便于后续运算
        returnmat[1,:]=np.inf#距离初始化
        while flag:       
            flag=0
            minp=0
            for i in range(m):
                dismax=returnmat[1,i]#取出当前误差
                for j in range(k):#计算该点与每一个簇的误差，如果误差小于当前则更新数据
                    pointdist=dist(dataset[i],centroids[j])
                    if pointdist<dismax:
                        dismax=pointdist
                        minp=j
                if  dismax!=returnmat[1,i]:#只要有一个点进行了更新，那就要继续迭代下去
                    flag=1
                    returnmat[0,i]=minp
                    returnmat[1,i]=dismax
            for i in range(k) :#更新簇的数据
                ptsinclust = dataset[np.nonzero(returnmat[:, 0].A == i)[0]]
                if len(ptsinclust):#只有这个簇含有数据时才更新
                    centroids[i]=np.mean(ptsinclust,axis=0)
        self.centroids=centroids
        self.pointmat=returnmat
        return centroids,returnmat
    def loaddata(self,filename,n=1000,m=1):
        a=pd.read_csv(filename)#读取文件默认读取前n行第m列起
        a=a.values       
        return a[:n,m:]
def sigmod(xmat,w):
    m=-xmat*w
    return 1/(1+np.exp(m))
def gradientdescent(w,xmat,ymat,alpha=0.001,operate=sigmod):
    H=operate(xmat,w)#梯度下降法
    dw=xmat.T*(H-ymat)
    w=w-alpha*dw
    return w
class logicalreturn():
    def __int__(self):
        return 0
    def logicalturn(self,xmat,ymat,alpha=0.001,maxrenew=20000,operate=gradientdescent):
        #XMAT为mxn的矩阵，ymat为mx1的矩阵
        n=np.shape(xmat)[1]
        w=np.mat(np.random.randn(n,1))
        for i in range(maxrenew):
            w=operate(w,xmat,ymat,alpha)
        self.w=w
        return w
    def loaddata(self,filename,n=1000,m=1):
        a=pd.read_csv(filename)#读取文件默认读取前n行第m列起
        a=a.values       
        x=a[:n,m:-1]
        y=a[:n,-1]
        return np.mat(x),np.mat(y).T
  
    



