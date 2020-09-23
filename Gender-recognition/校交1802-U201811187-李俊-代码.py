#!/usr/bin/env python
# coding: utf-8

# # HUST机器学习结课报告

# ## 基于语音识别的性别识别

# ### 校交1802李俊
# ---

# ## Part 1 

# In[1]:


import pandas as pd
import numpy as np
import random
import matplotlib.pyplot as plt
import re
import time

get_ipython().run_line_magic('matplotlib', 'inline')
# 读入数据
data = pd.read_csv("voice.csv")
print ("data read successfully.")
data.head(7)


# In[2]:


class SVM(object):
    """
    SVM model
    """
    def __init__(self, max_iter=10000, kernel_type='linear', C=1.0, epsilon=0.00001):
        self.max_iter = max_iter
        self.kernel_type = kernel_type
        self.kernel_func_list = {
            'linear': self._kernel_linear,
            'quadratic': self._kernel_quadratic,
        }
        self.kernel_func = self.kernel_func_list[kernel_type]
        self.C = C
        self.epsilon = epsilon
        self.alpha = None

    def train_raw(self, X_train, Y_train):
        """
        Training model
        :param X_train: shape = num_train, dim_feature
        :param Y_train: shape = num_train, 1
        :return: loss_history
        """
        n, d = X_train.shape[0], X_train.shape[1]
        self.alpha = np.zeros(n)
        # Iteration
        for i in range(self.max_iter):
            diff = self._iteration(X_train, Y_train)
            if i % 100 == 0:
                print('Iter %r / %r, Diff %r' % (i, self.max_iter, diff))
            if diff < self.epsilon:
                break

    def predict_raw(self, X):
        return np.dot(self.w.T, X.T) + self.b

    def predict(self, X):
        return np.sign(np.dot(self.w.T, X.T) + self.b).astype(int)

    def _iteration(self, X_train, Y_train):
        alpha = self.alpha
        alpha_prev = np.copy(alpha)
        n = alpha.shape[0]
        for j in range(n):
            # Find i not equal to j randomly
            i = j
            for _ in range(1000):
                if i != j:
                    break
                i = random.randint(0, n - 1)
            x_i, x_j, y_i, y_j = X_train[i, :], X_train[j, :], Y_train[i], Y_train[j]
            # Define the similarity of instances. K11 + K22 - 2K12
            k_ij = self.kernel_func(x_i, x_i) + self.kernel_func(x_j, x_j) - 2 * self.kernel_func(x_i, x_j)
            if k_ij == 0:
                continue
            a_i, a_j = alpha[i], alpha[j]
            # Calculate the boundary of alpha
            L, H = self._cal_L_H(self.C, a_j, a_i, y_j, y_i)
            # Calculate model parameters
            self.w = np.dot(X_train.T, np.multiply(alpha, Y_train))
            self.b = np.mean(Y_train - np.dot(self.w.T, X_train.T))
            # Iterate alpha_j and alpha_i according to 'Delta W(a_j)'
            E_i = self.predict(x_i) - y_i
            E_j = self.predict(x_j) - y_j
            alpha[j] = a_j + (y_j * (E_i - E_j) * 1.0) / k_ij
            alpha[j] = min(H, max(L, alpha[j]))
            alpha[i] = a_i + y_i * y_j * (a_j - alpha[j])
        diff = np.linalg.norm(alpha - alpha_prev)
        return diff

    def _kernel_linear(self, x1, x2):
        return np.dot(x1, x2.T)

    def _kernel_quadratic(self, x1, x2):
        return np.dot(x1, x2.T) ** 2

    def _cal_L_H(self, C, a_j, a_i, y_j, y_i):
        if y_i != y_j:
            L = max(0, a_j - a_i)
            H = min(C, C - a_i + a_j)
        else:
            L = max(0, a_i + a_j - C)
            H = min(C, a_i + a_j)
        return L, H

def _GenerateData():
    k, m, n_train, n_val = 5, 2, 5, 2
    X_train, X_val, Y_train, Y_val = [], [], [], []
    color = ['c', 'g', 'b', 'r']
    def _generateOne(X, Y, i):
        x, y, l = random.uniform((int(i / 2) + 0.1) * 10, (int(i / 2) + 0.9) * 10), random.uniform((i % 2 * 0.5 + 0.1) * 10, (i % 2 * 0.5 + 0.9) * 10), i
        X.append((x, y))
        Y.append((i - 0.5)*2)
        return x, y
    for i_ in range(m):
        for _ in range(n_train):
            x_, y_ = _generateOne(X_train, Y_train, i_)
            plt.scatter(x_, y_, s=100, c=color[i_])
        for _ in range(n_val):
            _generateOne(X_val, X_val, i_)

    return np.array(X_train), np.array(X_val), np.array(Y_train), np.array(Y_val)


# In[3]:


print(data.info())


# In[4]:


data.label.unique


# In[5]:


data.label=[1 if each =="female" else 0 for each in data.label]
data.label.values


# In[6]:


data.head(6)#first six


# In[7]:


y=data.label.values
x_data=data.drop(['label'],axis=1)


# In[8]:


np.min(x_data)


# In[9]:


np.max(x_data)


# In[10]:


#normalization
x=(x_data-np.min(x_data))/(np.max(x_data)-np.min(x_data)).values


# In[11]:


#train test split
from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test=train_test_split(x,y, test_size=0.2, random_state=42)
#find transpose
x_train=x_train.T
x_test=x_test.T
y_train=y_train.T
y_test=y_test.T
print("x_train shape:",x_train.shape)
print("x_test shape:",x_test.shape)
print("y_train shape:",y_train.shape)
print("y_test shape:",y_test.shape)


# In[12]:


#parameter initialize and sigmoid function
def initialize_weights_and_bias(dimension):
    w=np.full((dimension,1),0.01)
    b=0.0
    return w,b
def sigmoid(z):
    y_head=1/(1+np.exp(-z))
    return y_head


# In[13]:


def forward_backward_propagation(w,b,x_train,y_train):
    z = np.dot(w.T,x_train) + b
    y_head = sigmoid(z)
    loss = -y_train*np.log(y_head)-(1-y_train)*np.log(1-y_head)
    cost = (np.sum(loss))/x_train.shape[1]    
    derivative_weight = (np.dot(x_train,((y_head-y_train).T)))/x_train.shape[1] 
    derivative_bias = np.sum(y_head-y_train)/x_train.shape[1]  
    gradients = {"derivative_weight": derivative_weight, "derivative_bias": derivative_bias}
    
    return cost,gradients


# In[14]:


def update(w, b, x_train, y_train, learning_rate,number_of_iterarion):
    cost_list = []
    cost_list2 = []
    index = []
    
    for i in range(number_of_iterarion):
        cost,gradients = forward_backward_propagation(w,b,x_train,y_train)
        cost_list.append(cost)
        w = w - learning_rate * gradients["derivative_weight"]
        b = b - learning_rate * gradients["derivative_bias"]
        if i % 10 == 0:
            cost_list2.append(cost)
            index.append(i)
            
    parameters = {"weight": w,"bias": b}
    return parameters, gradients, cost_list


# In[15]:


def predict(w,b,x_test):
    z = sigmoid(np.dot(w.T,x_test)+b)
    Y_prediction = np.zeros((1,x_test.shape[1]))
    for i in range(z.shape[1]):
        if z[0,i]<= 0.5:
            Y_prediction[0,i] = 0
        else:
            Y_prediction[0,i] = 1

    return Y_prediction


# In[16]:


def main(x_train, y_train, x_test, y_test, learning_rate ,  para):
    # initialize
    model = SVM()
    dimension =  x_train.shape[0]
    w,b = initialize_weights_and_bias(dimension)
    parameters, gradients, cost_list = update(w, b, x_train, y_train, learning_rate,para)
    y_prediction_test = predict(parameters["weight"],parameters["bias"],x_test)
    print("test accuracy: {} %".format(100 - np.mean(np.abs(-0.1+y_prediction_test - y_test)) * 100))
    
main(x_train, y_train, x_test, y_test,learning_rate = 1, para = 300)


# ## Part 2 

# ## 1.分析数据

# In[1]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

get_ipython().run_line_magic('matplotlib', 'inline')
# 读入数据
data = pd.read_csv("voice.csv")
print ("data read successfully.")
data.head(7)


# In[2]:


data.corr()


# In[3]:


data.isnull().sum()


# In[4]:


print ('Total number of samples:{}'.format(data.shape[0]))
print ('Total number of male:{}'.format(data[data.label == 'male'].shape[0]))
print ('Total number of female:{}'.format(data[data.label == 'female'].shape[0]))


# ## 2.可视化数据

# 将特征两两配对，查看性别关于所有特征对的分布。将分布图保存在figure的文件夹下。

# In[5]:


import os

def show_relevence():
    # 以两个特征为一组查看样本分布
    data = pd.read_csv("voice.csv")
    female = data[data.label == 'female']
    male = data[data.label == 'male']
    indices = list(data.drop(['label'], axis=1).columns)
    if not os.path.exists('figure'):
        os.mkdir('figure')
    for feature_x in indices:
        for feature_y in indices[indices.index(feature_x):]:
            plt.figure(figsize=(8,6))
            X = male[feature_x]
            Y = male[feature_y]
            plt.scatter(X, Y, c='orange', label='male', alpha = 0.8)
            
            X = female[feature_x]
            Y = female[feature_y]
            plt.scatter(X, Y, c='blue', label='female', alpha = 0.2)
            
            plt.xlabel(feature_x)
            plt.ylabel(feature_y)
            plt.legend(loc='upper right')
            #plt.show()            
            plt.savefig('figure/{}-{}.png'.format(feature_x, feature_y))
            
        break

              
show_relevence()


# ## 3.数据预处理

# In[6]:


from sklearn.utils import shuffle

# 打乱原始数据顺序
data = shuffle(data, random_state=0)

gender = data.label
features = data.drop(['label'], axis=1)
print ("data is ready.")


# ### 3.1标准化数据

# In[7]:


from sklearn.preprocessing import StandardScaler

def standard_data(data):
    scaler = StandardScaler()
    scaler.fit(data)
    return scaler.transform(data)

features = standard_data(features)
print ("data has been standarded.")


# ### 3.2划分训练集和测试集

# In[8]:


from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test =         train_test_split(features, gender, train_size = 0.80, random_state = 0)
print ("Training and testing split was successful")


# ## 4.训练模型

# In[9]:


from sklearn.metrics import accuracy_score


def train_clf(clf, X_train, y_train):
    clf.fit(X_train,y_train)
    print ("Classifier trained successfully.")

def predict_labels(clf, features):
    y_pred = clf.predict(features)
    return y_pred
    
def train_predict(clf, X_train, y_train, X_test, y_test):
    
    # 输出训练器名称
    print ("Classifier：{}....".format(clf.__class__.__name__))
    
    # 训练一个分类器
    train_clf(clf, X_train, y_train)
    
    # 输出训练集和训练集预测结果
    print ("Accuracy for train set: {}".format(accuracy_score(y_train, predict_labels(clf, X_train))))
    print ("Accuarcy for test set: {}".format(accuracy_score(y_test, predict_labels(clf, X_test))))


# ### 4.1基准对比

# In[10]:


from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn import svm

clf_A = RandomForestClassifier(n_estimators=10)
clf_B = DecisionTreeClassifier()
clf_C = svm.SVC(gamma='auto')

for clf in clf_A, clf_B, clf_C:
    train_predict(clf, X_train, y_train, X_test, y_test)


# ## 5.调试支持向量机模型

# ### 5.1对比核函数对模型影响

# In[11]:


from sklearn.model_selection import cross_val_score

# 核函数列表
kernels = ['linear', 'rbf', 'poly']
acc_score = []
for k in kernels:
    svc= svm.SVC(kernel=k, gamma='auto')
    scores = cross_val_score(svc, features, gender, cv=5 ,scoring='accuracy')
    acc_score.append(np.mean(scores))

# 输出各个核函数得分
print ('The accuracy of SVM with linear kernel: ', acc_score[0])
print ('The accuracy of SVM with rbf kernel: ', acc_score[1])
print ('The accuracy of SVM with poly kernel: ', acc_score[2])


# ### 5.2调试参数C

# In[12]:


get_ipython().run_line_magic('matplotlib', 'inline')

from sklearn.model_selection import cross_val_score

# C的取值范围
c_range = np.arange(1, 20)
acc_score = []
for c in c_range:
    svc=svm.SVC(kernel='rbf', C=c, gamma='auto')
    scores = cross_val_score(svc, features, gender, cv=5, scoring='accuracy') #cv is cross validation
    acc_score.append(np.mean(scores))
        
# 显示准确率和C的关系
plt.figure(figsize=(8,6))
plt.plot(c_range, acc_score)
plt.xticks(np.arange(0, 20, 2))
plt.xlabel("Value of C for SVM")
plt.ylabel("Cross-Validation Scores")
plt.show()


#    从图中可以看出，准确率随着参数C的增大而增大。参数C取值在18左右是准确率达到最大。此时准确率大约为98.30%。接下来将参数C的取值缩小到17.0到19.0之间查看准确率的变化情况。

# In[13]:


get_ipython().run_line_magic('matplotlib', 'inline')

# C的取值范围
c_range = np.arange(17.0, 19.0, 0.2)
acc_score = []
for c in c_range:
    svc=svm.SVC(kernel='rbf', C=c, gamma='auto')
    scores = cross_val_score(svc, features, gender, cv=5, scoring='accuracy') #cv is cross validation
    acc_score.append(np.mean(scores))

# 显示准确率和C的关系
plt.figure(figsize=(8, 6))
plt.plot(c_range, acc_score)
plt.xticks(c_range)
plt.xlabel("Value of C for SVM")
plt.ylabel("Cross-Validation Scores")
plt.show()


# 参数C在17.4时，模型准确率最高。

# ### 5.3调试参数gamma

# In[14]:


get_ipython().run_line_magic('matplotlib', 'inline')

# gamma参数列表
gamma_range=[0.0001,0.001,0.01,0.1,1,10,100]
acc_score = []

for gamma in gamma_range:
    svc = svm.SVC(kernel='rbf', gamma=gamma)
    scores = cross_val_score(svc, features, gender, cv = 5, scoring='accuracy')
    acc_score.append(np.mean(scores))

# 显示准确率和gamma之间的关系
plt.figure(figsize=(8, 6))
plt.plot(gamma_range,acc_score)
plt.xlabel('Value of gamma for SVM ')
plt.xticks(np.arange(-5, 100, 5))
plt.ylabel('Cross-Validated Accuracy')
plt.show()


# 当gamma取值在0.1左右时，准确率达到最高。接下来将gamma取值限制在0.01到0.15之间，查看准确率。

# In[15]:


get_ipython().run_line_magic('matplotlib', 'inline')

# gamma参数列表
gamma_range = np.arange(0.01, 0.15, 0.01)
acc_score = []
for gamme in gamma_range:
    svc = svm.SVC(kernel='rbf', gamma=gamme)
    scores = cross_val_score(svc, features, gender, cv = 5, scoring='accuracy')
    acc_score.append(np.mean(scores))

# 显示准确率与gamma的关系
plt.figure(figsize=(8, 6))
plt.plot(gamma_range,acc_score)
plt.xlabel('Value of gamma for SVM ')
#plt.xticks(np.arange(-5, 100, 5))
plt.ylabel('Cross-Validated Accuracy')
plt.show()


# 从图中可以看出,准确率随着参数gamma增大而增大，在gamma等于0.10时达到最大值。此时准确率约为98.20%

# ### 5.4同时调试多个参数

# In[16]:


from sklearn.model_selection import GridSearchCV

# 参数字典
params = tuned_parameters = {
 'C': (np.arange(0.1,1.0,0.1)) , 'kernel': ['linear'],
 'C': (np.arange(15.5,18.5,0.5)) , 'gamma': np.arange(0.01, 0.20, 0.05), 'kernel': ['rbf']
}
grid_obj = GridSearchCV(estimator=clf,
                param_grid=params,
                scoring='accuracy',
                cv=5)
grid_obj.fit(features, gender)
clf = grid_obj.best_estimator_

print ('The best model parameters: ', grid_obj.best_params_)
print ('The best model score: ', grid_obj.best_score_)


# ## 6.结果分析

# ### 6.1学习曲线

# In[17]:


from sklearn.model_selection import learning_curve

get_ipython().run_line_magic('matplotlib', 'inline')

def show_learning_curve(clf, X_train, y_train):
    train_sizes, train_scores, test_scores = learning_curve(estimator=clf,
                                                       X=X_train,
                                                       y=y_train,
                                                       train_sizes=np.linspace(0.1, 1.0, 10),
                                                       cv=10)

    # 训练集集平均准确率
    train_mean = np.mean(train_scores, axis=1)

    # 训练集方差
    train_std = np.std(train_scores, axis=1)

    # 测试集平均准确率和方差
    test_mean = np.mean(test_scores, axis=1)
    test_std = np.std(test_scores, axis=1)

    # 训练集曲线设置
    plt.plot(train_sizes, train_mean, color='red', marker='o', label='Training Accuracy')
    # 训练集曲线范围
    plt.fill_between(train_sizes,
                train_mean + train_std,
                train_mean - train_std,
                alpha=0.15, color='red')

    # 测试集曲线设置
    plt.plot(train_sizes, test_mean, color='blue', linestyle='--', marker='s', 
        label='Test Accuracy')
    plt.fill_between(train_sizes,
                test_mean + test_std,
                test_mean - test_std,
                alpha=0.15, color='blue')

    plt.xlabel('Number of training samples')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()
    
show_learning_curve(clf,features, gender)


# ### 6.2收集被错误预测的样本

# In[18]:


clf = grid_obj.best_estimator_
pred = clf.predict(features)
wrong_pred = gender[pred != gender]
wrong_samples = []

# 将错误预测的样本加入wrong_pred
for i in wrong_pred.index:   
    row = data.loc[i]
    row['label'] = row['label'] + ' in SVM'
    wrong_samples.append(row)
            
pd.DataFrame(wrong_samples).to_csv('wrong_pred.csv')

print ('wrong data has been collected.')


# ### 6.3可视化异常分类样本的分布

# In[19]:


import seaborn

get_ipython().run_line_magic('matplotlib', 'inline')

# 合并原始样本和异常分类样本
data = pd.read_csv("voice.csv")
wrong_data = pd.read_csv("wrong_pred.csv")
data = pd.concat([data, wrong_data])

gender = data.label
features = data.drop(['label'], axis=1)
seaborn.pairplot(data[['meanfreq', 'IQR', 'meanfun', 'label']], 
            hue='label', palette="husl", markers=["o", "o", "s", "D"], height=3)
plt.show()


# ### 6.4输出最优模型在交叉验证上的准确率

# In[20]:


# 获取最优模型
clf = svm.SVC(kernel='rbf', C=1.3, gamma=0.2)

data = pd.read_csv("voice.csv")
data = shuffle(data, random_state=0)
features = data.drop(['label'], axis=1)
gender = data.label
features = standard_data(features)
scores = cross_val_score(clf, features, gender, cv = 5, scoring='accuracy')

print ('Accuracy of the best model by cross_val_score:', np.mean(scores))

