#QApplication和QWidget
import sys
from PyQt5.QtWidgets import QApplication,QWidget
if __name__ == "__main__":
    #创建QApplication类的实例
    app = QApplication(sys.argv)
    #创建一个窗口
    Windows = QWidget()
    #设置窗口的尺寸
    Windows.resize(600,800)
    Windows.move(300,300)
    #设置窗口的标题
    Windows.setWindowTitle("第一个PyQt5的应用")
    Windows.show()
    #进行程序的主循环，并通过exit()函数确保主循环安全结束
    sys.exit(app.exec_())