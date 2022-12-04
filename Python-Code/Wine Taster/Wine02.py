# -*- coding: utf-8 -*-
"""
Created on Sun Nov 21 13:55:16 2021

@author: Scottie
"""


import pandas 

from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split 
from sklearn.naive_bayes import GaussianNB
from sklearn import metrics

import pydotplus
import matplotlib.pyplot as plt
import matplotlib.image as pltimg





#Read in the File
f=pandas.read_csv("WineData.csv")
f.head()


#Mapping the traits to numbers so that I can work with the data

color={'red':0, 
       'white':1, 
       'other':2}
like={'yes':1,
      'no':0}


#f['Variety']=f['Variety'].map(variety)
f['Color']=f['Color'].map(color)
#f['Location']=f['Location'].map(location)
f['Like?']=f['Like?'].map(like) 

f.drop(columns=['Wine Name'],inplace=True)
f=pandas.get_dummies(f,columns=['Variety','Location'])
target=f['Like?']
f.drop(columns=['Like?'],inplace=True)


## Split the data into train and test data
## Where y_train is the actual data
x_train, x_test, y_train, y_test=train_test_split(f,target,shuffle=False, train_size=50)

WineTree=DecisionTreeClassifier()
Wineknn = KNeighborsClassifier(n_neighbors = 3)
Winegaussian = GaussianNB() 


##  Fit the data to the alorithm

WineTree=WineTree.fit(x_train,y_train)
Wineknn.fit(x_train, y_train)
Winegaussian.fit(x_train, y_train) 



##  Predictions
tree_pred=WineTree.predict(x_test)
knn_pred = Wineknn.predict(x_test)
gaus_pred =Winegaussian.predict(x_test)
    ## get only the false positive rate
tree_proba=WineTree.predict_proba(x_test)[:,1]
knn_proba=Wineknn.predict_proba(x_test)[:,1]
gaus_proba=Winegaussian.predict_proba(x_test)[:,1]


##Get Confusion matrices

TreeCF=metrics.confusion_matrix(y_test, tree_pred)
knnCF =metrics.confusion_matrix(y_test, knn_pred)
GausCF=metrics.confusion_matrix(y_test, gaus_pred)


metrics.ConfusionMatrixDisplay(TreeCF).plot()
metrics.ConfusionMatrixDisplay(knnCF ).plot()
metrics.ConfusionMatrixDisplay(GausCF).plot()

plt.show()




## Plot ROC curves

tree_roc_score=metrics.roc_auc_score(y_test, tree_proba)
knn_roc_score=metrics.roc_auc_score(y_test, knn_proba)
gaus_roc_score=metrics.roc_auc_score(y_test, gaus_proba)

print('roc_auc_score for DecisionTree: ',tree_roc_score)
print('roc_auc_score for KNN: ',knn_roc_score)
print('roc_auc_score for Gaussian: ',gaus_roc_score)

    ## Got how to plot the ROC curves from the YouTube Link in the references
 
tree_fpr, tree_tpr, _ = metrics.roc_curve(y_test, tree_proba)
knn_fpr, knn_tpr, _ = metrics.roc_curve(y_test, knn_proba)
gaus_fpr, gaus_tpr, _ = metrics.roc_curve(y_test, gaus_proba)



plt.plot(tree_fpr, tree_tpr, linestyle='--', label='DecisionTree (AUROC = %0.3f)' % tree_roc_score)
plt.plot(knn_fpr, knn_tpr, marker='.', label='KNearest Neighbor(AUROC = %0.3f)' % knn_roc_score)
plt.plot(gaus_fpr, gaus_tpr, marker='.', label='Gaussian NB(AUROC = %0.3f)' % gaus_roc_score)

# Title
plt.title('ROC Curve')
# Axis labels
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
# Show legend
plt.legend() # 
# Show plot
plt.show()


## Plot Decision Tree
    ## got this from W3schools site
data = tree.export_graphviz(WineTree, out_file=None,feature_names=list(f.columns.values))
graph = pydotplus.graph_from_dot_data(data)
graph.set_size("30,30!")
graph.write_png('mydecisiontree.png')

img=pltimg.imread('mydecisiontree.png')
imgplot = plt.imshow(img)
plt.show()


