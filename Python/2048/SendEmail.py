# !/usr/bin/python
# -*- coding: UTF-8 -*-

import smtplib
from email.mime.text import MIMEText
from email.utils import formataddr
# from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart
# from email.mime.application import MIMEApplication
# from email.utils import parseaddr, formataddr, formatdate
from email.header import Header

my_sender = '13135540882@163.com'  # 发件人邮箱账号
my_pass = "ROIYXTALMCGICZCK"  # 发件人邮箱密码
my_user = 'wytmxutao@nuaa.edu.cn'  # 收件人邮箱账号，我这边发送给自己


def mail():
    ret = True
    try:
        # # 创建一个带附件的实例,126 & yeah邮箱会检测为垃圾文件，无法发送！
        message = MIMEMultipart()
        message['From'] = Header("remote deskyop", 'utf-8')
        message['To'] = Header("user", 'utf-8')
        subject = '编号赛事参与信息已获取'
        message['Subject'] = Header(subject, 'utf-8')
        #
        # # 邮件正文内容
        message.attach(MIMEText('编号至的用户参与赛事信息表格已保存! 请及时查看服务器信息！', 'plain', 'utf-8'))
        # filename = './user_done_participant/test{}.xls'.format(str(numindex))
        # part = MIMEApplication(open(filename, 'rb').read())
        # part.add_header('Content-Disposition', 'attachment', filename=filename)
        # message.attach(part)

        msg = MIMEText('现发送测试邮件', 'plain', 'utf-8')
        msg['From'] = formataddr(["FromRunoob", my_sender])  # 括号里的对应发件人邮箱昵称、发件人邮箱账号
        msg['To'] = formataddr(["FUser", my_user])  # 括号里的对应收件人邮箱昵称、收件人邮箱账号
        msg['Subject'] = "测试邮件推送"  # 邮件的主题，也可以说是标题

        server = smtplib.SMTP_SSL("smtp.yeah.net", 465)  # 发件人邮箱中的SMTP服务器，端口是465
        server.login(my_sender, my_pass)  # 括号中对应的是发件人邮箱账号、邮箱密码
        server.sendmail(my_sender, [my_user, ], msg.as_string())  # 括号中对应的是发件人邮箱账号、收件人邮箱账号、发送邮件
        server.quit()  # 关闭连接
    except smtplib.SMTPException as e:  # 如果 try 中的语句没有执行，则会执行下面的 ret=False
        ret = False
        print(e)

    if ret:
        print("邮件发送成功")
    else:
        print("邮件发送失败")

    return ret


mail()
