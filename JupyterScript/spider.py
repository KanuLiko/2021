def main():
    baseurl = "https://movie.douban.com/top250?start="
    #爬取网页
    datalist = getData(baseurl)
    savepath = "D:\\DownloadFiles\\doubanTop250.xls"
    #保存数据
    saveData(savepath)

#爬取网页
def getData(baseurl):
    datalist = []
    #逐一解析数据
    return datalist

#得到指定网页的一个内容
def askUrl(url):
    header = {}

#保存数据
def saveData(savePath):
    print("save...")

if __name__ = "__main__":
    main()

