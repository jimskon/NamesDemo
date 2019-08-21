
from sortedcontainers import SortedDict
filePath="/home/class/SoftDev/namedata/"

class NameInfo:
  """
  Class to store information about the 
  Statistics of names.
  For each name type, there is a dict
  for each name, there is a list of name %, cumulative %, rank
  """
  def __init__(self, num : int):
    """ 
    create a NameInfo Structure
    num is the number of types of names
    """
    self.nameData=[]
    for i in range(num):
      self.nameData.append([])
  def addNames(self, nameFile, index : int):
    """
    create a new list of names with data
    given an index within range of 0..num-1
    """
    names = open(filePath+nameFile)
    nameDict=SortedDict()
    for line in names:
      line=line.strip()
      data=line.split()
      numData=data[1:]
      numData[0] = float(numData[0])
      numData[1] = float(numData[1])
      numData[2] = int(numData[2])
      nameDict[data[0]]=numData
    self.nameData[index]=nameDict
    return
  def lookup(self,name,index):
    """
    lookup name in specified index
    return list of [%,%cum,rank] if in list
    else return none
    """
    return self.nameData[index].get(name)

  def lookup10(self,name,index):
    """
    lookup name in specified index
    return list of [%,%cum,rank] if in list
    else return none
    """
    i=self.nameData[index].bisect_right(name)
    print(i)
    low = max(0,i-5)
    high = min(len(self.nameData[index]),i+5)
    result=[]
    for j in range(low,high):
      result.append(self.nameData[index].peekitem(j))
    return result


def lookup(name,data):
  print(data[name])

nameInfo=NameInfo(3)
nameInfo.addNames('dist.female.first',0)
nameInfo.addNames('dist.male.first',1)
nameInfo.addNames('dist.all.last',2)

name=input("Name:").upper()
type=int(input("1=female,2=male,3=last: "))

data=nameInfo.lookup(name,type-1)
print(data)
data=nameInfo.lookup10(name,type-1)
print(data)

