#使用线程类来实现计数器

import sys
from PyQt5 import QtWidgets
from PyQt5.QtCore import*
from PyQt5.QtGui import*
from PyQt5.QtWidgets import*

sec = 0
class WorkThread(QThread):
    timer = pyqtSignal() #每个一秒发送一个信号
    end = pyqtSignal() #计数完成时发送信号
    def run(self):
        while(True):
            self.sleep(1)
            if sec == 5:
                self.end.emit()
                break
            self.timer.emit() #发送timer信号

class Counter(QWidget):
    def __init__(self,parent=None):
        super(Counter,self).__init__(parent)
        self.setWindowTitle("计数器")
        self.resize(300,120)

        layout = QVBoxLayout()
        self.lcdNumber = QLCDNumber()
        layout.addWidget(self.lcdNumber)

        button = QPushButton("开始计数")
        layout.addWidget(button)
        
        self.workThread =WorkThread()

        self.workThread.timer.connect(self.countTime)
        self.workThread.end.connect(self.end)

        button.clicked.connect(self.work)

    def countTime(self):
        global sec
        sec +=1
        self.lcdNumber.display(sec)
    def end(self):
        QMessageBox(self,"消息","计数结束",QMessageBox.Ok)
    def work(self):
        self.workThread.start()

if '__name__'=='__main__':
    app = QApplication(sys.argv)
    form = Counter()
    form.show()
    sys.exit(app.exec_())