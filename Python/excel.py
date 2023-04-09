import pandas as pd

file = r'C:\Users\sbb\Documents\WeChat Files\wxid_53o2l0h3up6z12\FileStorage\File\2023-03\论文数据汇总.xlsx'


# 打开excel，读取sheet2
# https://pandas.pydata.org/docs/reference/api/pandas.read_excel.html#
workbook = pd.read_excel(file,'Sheet2')
# 输出标签
#print(list(workbook.keys()))

print(workbook)
# 访问第一行第二列
print(workbook.iloc[1,2])

print(workbook.iloc[0,0],end=' ')
print(workbook.iloc[0,2],end=' ')
print(workbook.iloc[0,3],end=' ')
print(workbook.iloc[0,4],end=' ')
print(workbook.iloc[0,5],end=' ')
print(workbook.iloc[0,6],end=' ')
print(workbook.iloc[0,7],end=' ')
