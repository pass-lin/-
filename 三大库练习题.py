# -*- coding: utf-8 -*-
"""
Created on Tue Apr  7 16:45:16 2020

@author: Administrator
"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
#Create a null vector of size 10
np.zeros(10)
#Create a null vector of size 10 but the fifth value which is 1 
np.ones(10)
#Create a vector with values ranging from 10 to 49 
np.arange(10,50)
#Create a 3x3 matrix with values ranging from 0 to 8 
np.mat(np.arange(0,9).reshape(3,3))
#Create a 10x10 array with random values and find the minimum and maximum values
m=np.random.random((10, 10))
maxvalues=np.max(m)
minvalues=np.min(m)
#Create a 2d array with 1 on the border and 0 inside 
m,n=10,10
a=np.zeros((m,n))
a[0,:]=1
a[m-1,:]=1
a[:,0]=1
a[:,n-1]=1
#Multiply a 5x3 matrix by a 3x2 matrix (real matrix product) 
m=np.mat(np.random.random((5, 3)))
n=np.mat(np.random.random((3, 2)))

#panda
data = {'animal': ['cat', 'cat', 'snake', 'dog', 'dog', 'cat', 'snake', 'cat', 'dog', 'dog'],
        'age': [2.5, 3, 0.5, np.nan, 5, 2, 4.5, np.nan, 7, 3],
        'visits': [1, 3, 2, 3, 2, 3, 1, 1, 2, 1],
        'priority': ['yes', 'yes', 'no', 'yes', 'no', 'no', 'no', 'yes', 'no', 'no']}

labels = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']
#Create df with labels as index
df=df=pd.DataFrame(data)
#Show df basic information and its data
df.describe()
#Select only the 'animal' and 'age' columns
df[['animal','age']]
#select the row with missing value,
df.isnull().T.any()
#Sort DF in descending age and ascending visit order
df.sort_values(by='age',ascending=True)
df.sort_values(by='age',ascending=False)
#In the 'animal' column, replace 'Snake' with 'Python'
df.replace({'snake':'Python'})

#matplotlib
import seaborn as sns
data = sns.load_dataset("iris")
#Size relationship between sepal and petal (scatter diagram)
plt.scatter(data['sepal_length'],data['petal_length'])
plt.scatter(data['sepal_width'],data['petal_width'])
#The size relationship between sepals and petals of iris of different species
plt.scatter(data[data['species']=='setosa']['sepal_length'],data[data['species']=='virginica']['sepal_width'])
#Distribution of sepals and petal sizes of different Iris species (box diagram)
a1=data[data['species']=='setosa']
a2=data[data['species']=='virginica']
plt.boxplot ([a1['sepal_width'],a1['petal_length'],a1['sepal_width'],a1['petal_width']])
plt.boxplot ([a2['sepal_width'],a2['petal_length'],a2['sepal_width'],a2['petal_width']])