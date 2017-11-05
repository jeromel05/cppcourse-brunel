
# coding: utf-8

# In[24]:


import pylab as pl


# In[25]:


import numpy as np


# In[26]:


data = np.genfromtxt('data.txt')


# In[27]:


select= np.array([d for d in data if d[1] < 30])
data1 = select.transpose()
pl.scatter(0.1 * data1[0], data1[1], alpha =0.8, edgecolors ='none');
pl.show();

n, bins, patches = pl.hist(0.1 * data1[0], 50, normed=0, alpha=0.75);
pl.show();
