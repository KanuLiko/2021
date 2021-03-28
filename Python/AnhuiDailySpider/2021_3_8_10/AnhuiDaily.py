# -*- coding: utf-8 -*-
import requests
import time
import xlwt
import xlrd
import re
import os
import threading

s = requests.session()
s.keep_alive = False


class AnhuiDailySpider():
    def __init__(self, KeyWords=["疫情"]):
        '''网页请求的两个重要参数'''
        self.cookies = "appmsglist_action_3871587551=card;pgv_info=;ssid=s3440732029;pgv_pvid=6722959450;pac_uid=0_f602d08734919;iip=0;ua_id=lKWt2kylAmnKBy0ZAAAAAH5upqryGmI9Qn1TLrPn5cA=;cert=Lb0Ykd5s6GEKDm0s1oohPIgxomUsqNR3; noticeLoginFlag=1; \
        remember_acct=2463852497%40qq.com; uuid=db1405446141133212c6c2c31813f663; rand_info=CAESIE/FiZSS0Un2yZVIQIqvqGNNiHnxrqSMAT0Zx0wXWa+A; slave_bizuin=3871587551; data_bizuin=3871587551; bizuin=3871587551;data_ticket=DkjRsuHkuBcQpBSyWkKETPJ+\
        ZrIZcjqfACfBq5nS4wWYz+2/YOzv7P8ncMNOPy/6;slave_sid=d0hGUzhLa2lXaU1qM0NVY2ZsVHl0REdES2FBTFowVlZtX3ZtNzZ6TnZHcmNMT3RpVUlCTWZxa3BLWHlQaEdqQmNqaUVhSG1UU205MmZBdTZiTXdJNWlja3VkT00xbEY1TXU1c01nOFVRcTBuNFRVa3hJaDJwZ0N1YmNkem1FTldIcDk2SVJXY0l2bT \
        g1aXM1;slave_user=gh_6ea353b6c849;xid=8f04b5fc9328c8cf366d5497f95a2085;openid2ticket_o37zD5m8wS8d1H6oQSG8H1UJ465o=;mm_lang=zh_CN;"
        self.DownloadHeaders = {
                        "Cookie": self.cookies,
                        "User-Agent": "Mozilla/5.0 (Linux; Android 10; STK-AL00 Build/HUAWEISTK-AL00; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/78.0.3904.62 XWEB/2759 MMWEBSDK/201201 Mobile Safari/537.36 MMWEBID/1378 \
                            MicroMessenger/8.0.1.1841(0x280001B6) Process/toolsmp WeChat/arm64 Weixin NetType/WIFI Language/zh_CN ABI/arm64"
        }
        '''新闻计数器'''
        self.NewsCount = 0
        '''新闻标题-新闻链接-新闻时间保存的位置'''
        self.workbook = xlwt.Workbook(encoding='utf-8')
        self.Worksheet = self.workbook.add_sheet('AuhuiDaily_articles')
        self.NewsPath = "AnhuiDaily.xls"
        '''新闻内容保存的位置'''
        self.NewsContentPath = "./Download/"
        '''获取新闻内容请求的相关参数'''
        self.GetContentHeaders = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.62 Safari/537.36"
        }
        '''爬取新闻链接的网址'''
        self.wechat_url = "https://mp.weixin.qq.com/cgi-bin/appmsg"
        '''新闻计数器'''
        self.NewsCount = 0
        '''方便断点续传的参数'''
        self.startPages = self.downloadPages()
        '''关键词下载选项'''
        self.KeyWords = KeyWords
        '''新闻中需要清洗的内容'''
        self.needClearWords = ['<!-- 注意：这个文件是一个公共文件，被很多地方引用，改动需要注意其他类型页面是否有受影响 -->', '安徽日报']
        self.createSavePath()

    def createSavePath(self):
        if not os.path.exists(self.NewsContentPath):
            os.mkdir(self.NewsContentPath)

    def downloadPages(self):
        AnhuiDaily = xlrd.open_workbook("downloadPages.xls")
        AnhuiDailyArticles = AnhuiDaily.sheets()[0]
        downloadPages = AnhuiDailyArticles.cell(0, 0).value
        return int(downloadPages)

    '''把时间戳转换为具体的事件点'''
    def timeStampTrans(timeStamp):
        timeArray = time.localtime(timeStamp)
        otherStyleTime = time.strftime("%y-%m-%d %H:%M:%S", timeArray)
        return otherStyleTime

    """
    需要提交的data
    以下个别字段是否一定需要还未验证。
    注意修改yourtoken,number
    number表示从第number页开始爬取，为5的倍数，从0开始。如0、5、10……
    token可以使用Chrome自带的工具进行获取
    fakeid是公众号独一无二的一个id，等同于后面的__biz
    """
    def downloadNewsUrls(self):
        '''检查下载了多少篇文章，断点续传'''
        for newsPage in range(self.startPages, 316):
            print("正在下载"+str(newsPage)+"页")
            data = {
                    "token": 1130076224,
                    "lang": "zh_CN",
                    "f": "json",
                    "ajax": "1",
                    "action": "list_ex",
                    "begin": str(newsPage),
                    "count": "5",
                    "query": "",
                    "fakeid": "MzA5NTc5ODQwMA==",
                    "type": "9",
            }
            '''使用get方法获取'''
            content_json = requests.get(self.wechat_url, headers=self.DownloadHeaders, params=data).json()
            '''返回了一个json，里面是每一页的数据'''
            beforeCount = self.NewsCount
            try:
                for item in content_json["app_msg_list"]:
                    NewsTitle = item['title']
                    Newslink = item['link']
                    NewsTime = self.timeStampTrans(item['create_time'])
                    SingleNews = [NewsTitle, Newslink, NewsTime]
                    for i in range(0, 3):
                        self.Worksheet.write(self.NewsCount, i, SingleNews[i])
                    self.NewsCount += 1
                print("第"+str(newsPage)+"页,"+"有"+str(self.NewsCount-beforeCount)+"篇新闻,"+"共"+str(self.NewsCount)+"篇新闻")
                time.sleep(3)
                self.workbook.save(self.savePath)
            except KeyError:
                if newsPage != self.downloadPages():
                    Pages = xlwt.Workbook(encoding='utf-8')
                    PageSheet = Pages.add_sheet('downloadPages')
                    PageSheet.write(0, 0, str(newsPage))
                    Pages.save("downloadPages.xls")
                else:
                    print("封号中")
                    break

    def downLoadArticles(self):
        for newsPage in range(0, 316):
            print("正在下载"+str(newsPage)+"页")
            data = {
                    "token": 271655701,
                    "lang": "zh_CN",
                    "f": "json",
                    "ajax": "1",
                    "action": "list_ex",
                    "begin": str(newsPage),
                    "count": "5",
                    "query": "",
                    "fakeid": 'MzA5NTc5ODQwMA==',
                    "type": "9",
                }
            # 使用get方法进行提交
            content_json = requests.get(self.url, headers=self.DownloadHeaders, params=data).json()
            # 返回了一个json，里面是每一页的数据
            for item in content_json["app_msg_list"]:
                NewsTitle = item['title']
                Newslink = item['link']
                NewsTime = self.StampTrans(item['create_time'])
                SingleNews = [NewsTitle, Newslink, NewsTime]
                for i in range(0, 3):
                    self.Worksheet.write(self.NewsCount+1, i, SingleNews[i])
                self.NewsCount += 1
                print(self.NewsCount)
            time.sleep(10)
            self.workbook.save(self.NewsPath)
        print("下载完成，一共是 "+str(self.NewsCount)+" 篇新闻")

    '''进行数据清洗'''
    def dataClear(self, data):
        for word in self.needClearWords:
            data = data.replace(word, '')
        return data

    def collectNewsContent(self, threads):
        totalPages = len(self.readUrl("AnhuiDaily_Part1.xls"))
        print("共有 "+str(totalPages) + " 条新闻需要下载")
        for index in range(1, 100):
            if totalPages % index == 0:
                thread_num = int(totalPages/index)
        print("开启了 "+str(thread_num)+" 个线程")
        each = totalPages/thread_num
        i = -1
        for i in range(int(thread_num)-1):
            startPage, endPage = int(i*each), int((i+1)*each)
            t = threading.Thread(target=ScrapyInfo, args=[self.DownloadHeaders, startPage, endPage])
            t.start()
            threads.append(t)
            time.sleep(1)
        t = threading.Thread(target=ScrapyInfo, args=(self.DownloadHeaders, startPage, endPage))
        t.start()
        threads.append(t)
        for thread in threads:
            thread.join()

    def readUrl(self, path):
        ArticlesUrls = []
        AnhuiDaily = xlrd.open_workbook(path)
        AnhuiDailyArticles = AnhuiDaily.sheets()[0]
        for newsIndex in range(AnhuiDailyArticles.nrows):
            if AnhuiDailyArticles.cell(newsIndex, 1) is None:
                break
            ArticlesUrls.append(AnhuiDailyArticles.cell(newsIndex, 1).value)
        return ArticlesUrls

    def readTitle(self, path):
        ArticlesTitle = []
        AnhuiDaily = xlrd.open_workbook(path)
        AnhuiDailyArticles = AnhuiDaily.sheets()[0]
        for newsIndex in range(AnhuiDailyArticles.nrows):
            if AnhuiDailyArticles.cell(newsIndex, 0) is None:
                break
            ArticlesTitle.append(AnhuiDailyArticles.cell(newsIndex, 0).value)
        return ArticlesTitle


def ScrapyInfo(headers, startPage, endPage):
    AnhuiDailyDemo = AnhuiDailySpider()
    Urls = AnhuiDailyDemo.readUrl(path="AnhuiDaily_Part1.xls")
    Titles = AnhuiDailyDemo.readTitle(path="AnhuiDaily_Part1.xls")
    for urlIndex in range(startPage, endPage):
        try:
            res = requests.get(url=Urls[urlIndex], headers=headers, timeout=30)
        except Exception as e:
            print("********产生了一个异常***********")
            print(e+"异常的链接: "+Urls[urlIndex])
            continue
        print(str(urlIndex)+" "+Titles[urlIndex])
        res.encoding = 'utf-8'
        NewsContent = AnhuiDailyDemo.dataClear(res.text)
        regex = re.compile(r'[\u4e00-\u9fa5]+')
        chineseResult = regex.findall(NewsContent)
        NewsContentString = ""
        for String in chineseResult:
            NewsContentString = NewsContentString+String
        with open(AnhuiDailyDemo.NewsContentPath+str(urlIndex)+".txt", "a+") as f:
            f.write(NewsContentString)


if __name__ == "__main__":
    '''放置线程的列表'''
    threads = []
    '''开启的线程的数量'''
    thread_nums = 400
    os.system("cls")
    KeyWords = ["疫情"]
    AnhuiDailyDemo = AnhuiDailySpider(KeyWords=KeyWords)
    AnhuiDailyDemo.collectNewsContent(threads)
