import urllib.request
from bs4 import BeautifulSoup
import re
import xlwt
from time import*
import requests
import numpy as np 
import matplotlib.pyplot as plt
import jieba 
import PIL.Image as image
from wordcloud import WordCloud
import os

class AnhuiScripy:
    '''初始化'''
    def __init__(self,url = "http://ah.anhuinews.com/hf/news/",ConWords=[],replaceWords=[]):
        self.header = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Safari/537.36 Edg/87.0.664.75"}
        self.url = url #默认收集这个网址
        self.Total = []
        self.spentTime = 0
        self.barColor = ['grey','gold','darkviolet','turquoise','r','g','b', 'c', 'm', 'y','k','darkorange','lightgreen','plum', 'tan',
'khaki', 'pink', 'skyblue','lawngreen','salmon']
        self.ConWords = ConWords
        self.replaceWords = replaceWords
    '''清除链接中某些不正常链接'''
    def clearUrl(self,data):
        result = []
        forbidChar = ['ttp','mssh','jhdd']
        for url in data:
            flag = True
            for string in forbidChar:
                if string in url[0]:
                    flag = False
            if flag:
                if 'html' in url[0]:
                    result.append(list(url))
        return result   
    def collectUrl(self,url="http://ah.anhuinews.com/hf/news/"):
        self.url = url
        beginTime = time()
        req = urllib.request.Request(url=self.url,headers=self.header)
        res = urllib.request.urlopen(req)
        html = res.read().decode("utf-8")
        pageContent = BeautifulSoup(html,"html.parser")
        pageContent = str(pageContent)
        news =re.compile(r'<a href=".(.*?)" target="_blank">(.*?)</a>')
        data = re.findall(news,pageContent)
        self.Total = self.Total+self.clearUrl(data)
        for i in range(1,6):
            temUrl = "http://ah.anhuinews.com/hf/news/index_"+str(i)+".html"
            req = urllib.request.Request(url=temUrl,headers=self.header)
            res = urllib.request.urlopen(req)
            html = res.read().decode("utf-8")
            pageContent = BeautifulSoup(html,"html.parser")
            pageContent = str(pageContent)
            news =re.compile(r'<a href=".(.*?)" target="_blank">(.*?)</a>')
            data = re.findall(news,pageContent)
            self.Total = self.Total+self.clearUrl(data)
        endTime = time()
        self.time = endTime-beginTime
    def getInfo(self):
        print("It has spent "+str(self.time)+"s!")
        print("Got "+str(len(self.Total))+" news totally!")
    def getNewsContent(self,newsName = "hefei.txt"):
        for htmlUrlIndex in range(int(len(self.Total))):
            newsUrl="http://ah.anhuinews.com/hf/news"+self.Total[htmlUrlIndex][0]
            print(newsUrl)
            newsTopic = self.Total[htmlUrlIndex][1]
            newsContent = self.handleNews(newsUrl=newsUrl)
            with open(newsName,'a',encoding = 'utf-8') as f:
                print("Downloading the "+str(htmlUrlIndex)+" article"+", "+str(round(htmlUrlIndex/int(len(self.Total))*100,2))+"%")
                f.write(newsTopic)
                f.write('\n')
                f.write('\n')
                for i in newsContent:
                    f.write(i)
            os.system("cls")
        print("Download Successfully,please ready to handle the data!")
    def handleNews(self,newsUrl):
        urlResponse = requests.get(newsUrl)
        urlResponse.encoding = "utf-8"
        urlSoup = BeautifulSoup(urlResponse.text,"html.parser")
        article = []
        for p in urlSoup.select('.info p')[:-1]:
            article.append(p.text.strip())
            for word in self.replaceWords:
                for line in article:
                    line.replace(word," ")
        return article
    def dataAnasys(self):
        with open("hf.txt",encoding="utf-8") as f:
            mytext = f.read()
        self.wordSigment = jieba.cut(mytext,cut_all=True)
        self.wordSigment = " ".join(self.wordSigment)
        self.barImage()
        self.wordCloudImage()
    def barImage(self):
        WordsCounts = np.zeros(int(len(self.ConWords)))
        WordsCollection = self.wordSigment.split(' ')
        for i in WordsCollection:
            for r in range(int(len(self.ConWords))):
                if i == self.ConWords[r]:
                    WordsCounts[r]=WordsCounts[r]+1
        print(self.ConWords,WordsCounts)
        plt.bar(self.ConWords,WordsCounts,color=self.barColor[0:len(ConWords)])
        plt.show()
    def wordCloudImage(self):
        mask = np.array(image.open(r"./news/images/wordcloud.jpeg"))
        wordcloud = WordCloud(
            mask = mask,
            scale = 1,
            font_path = "font.ttf"
        ).generate(self.wordSigment)
        image_produce = wordcloud.to_image()
        wordcloud.to_file(r"./news/images/new_wordcloud.jpg")
        image_produce.show()


ConWords = ['企业',"合肥","发展","建设","服务","活动","社区","工作"]
replaceWords=["的","在","和","等","了"]
url = "http://ah.anhuinews.com/hf/news/"
Spider = AnhuiScripy()
'''获得该网址的所有版块信息'''
req = urllib.request.Request(url='http://news.anhuinews.com/wzdt/',headers=Spider.header)
res = urllib.request.urlopen(req)
html = res.read().decode("utf-8")
pageContent = BeautifulSoup(html,"html.parser")
pageContent = str(pageContent)
news =re.compile(r'<a href="(.*?)" target="_blank">(.*?)</a>')
data = re.findall(news,pageContent)
for block in  data[1:17]:
    print("Downloading the "+"'"+block[0].split('/')[-2]+"'"+" news")
    if os.path.exists(block[0].split('/')[-2]+'.txt'):
        continue
    Spider = AnhuiScripy(url=block[0],ConWords=ConWords,replaceWords=replaceWords)
    Spider.collectUrl(url = block[0])
    Spider.getInfo()
    Spider.getNewsContent(newsName=r'./news/words/'+block[0].split('/')[-2]+'.txt')
    print('**************************************************')
Spider.dataAnasys()