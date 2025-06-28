from PyQt6 import QtWidgets
import sys
import os
from MyException import *

import second # Это конвертированный файл дизайна


class ExampleApp(QtWidgets.QMainWindow, second.Ui_MainWindow):
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.runButton.clicked.connect(self.change)

    def check_nums(self):
        num = self.numEditor.text()
        if not (num.isdigit()):
            raise MyException("Number contains unsupported symbols")

    def getResult1(self):
        char = self.numEditor.text()[0]
        res = 0
        for c in self.numEditor.text():
            if c == char:
                res += 1
        return res

    def getResult2(self):
        char_a = self.numASpin.text()[0]
        char_b = self.numBSpin.text()[0]

        return [(self.numEditor.text()[0] == char_a), (self.numEditor.text()[-1] == char_b)]

    def change(self):
        try:
            self.check_nums()
            self.errorLabel.setText("")
            self.result1.setText("The first digit occurred {} times".format(self.getResult1()))
            self.result2.setText("Number starts with A({}) - {} and end with B({}) - {}".format(
                self.numASpin.text()[0], self.getResult2()[0], self.numBSpin.text()[0], self.getResult2()[1]))
            
        except MyException as e:
            self.errorLabel.setText(e.message)


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = ExampleApp()
    window.show()
    app.exec()


if __name__ == '__main__':
    main()
