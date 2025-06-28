import logging
import sys

from PyQt6 import QtWidgets
import threading
import random
from datetime import datetime

import design2

logging.basicConfig(
    filename="/home/nedoletoff/Documents/tp/sample.log",
    format='%(asctime)s %(levelname)s %(message)s',
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S'
)
log = logging.getLogger("ex")


class ExampleApp(QtWidgets.QMainWindow, design2.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.run_button.clicked.connect(self.run)
        self.clear_button.clicked.connect(self.clear)
        self.enter_button.clicked.connect(self.enter_random)

    def run(self):
        try:
            t1 = datetime.now()
            self.run_no_thread()
            self.time_no_threads_label.setText("Время работы без потоков: " + str(datetime.now() - t1))
            t1 = datetime.now()
            self.run_with_thread()
            self.time_with_threads_label.setText("Время с потоками: " + str(datetime.now() - t1))
        except Exception as e:
            log.exception(e)
            t2 = datetime.now()
            self.error_label.setText("Ошибка ввода в таблицу - " + str(t2) + "\n" + str(e))
            self.clear()
        else:
            self.error_label.setText("")

    def run_with_thread(self):
        t = [threading.Thread(target=self.double_sum_label.setText, args=[str(self.get_double_sum())]),
             threading.Thread(target=self.index_label.setText, args=[self.get_index()])]
        for i in t:
            i.run()
        if self.has_pair():
            text = "2 пары соседних элементов с одинаковыми знаками найдены"
        else:
            text = "2 пары соседних элементов с одинаковыми знаками не найдены"
        self.result_3label.setText(text)

    def run_no_thread(self):
        self.double_sum_label.setText(str(self.get_double_sum()))
        self.index_label.setText(self.get_index())
        if self.has_pair():
            text = "2 пары соседних элементов с одинаковыми знаками найдены"
        else:
            text = "2 пары соседних элементов с одинаковыми знаками не найдены"
        self.result_3label.setText(text)

    def get_double_sum(self):
        double_sum = 0
        for i in range(10):
            if float(self.tableWidget.item(0, i).text()) > 0:
                double_sum += int(self.tableWidget.item(0, i).text())
        double_sum *= 2
        return double_sum

    def get_index(self):
        res = ''
        for i in range(1, 10):
            if int(self.tableWidget.item(0, i - 1).text()) < int(self.tableWidget.item(0, i).text()):
                res += ' ' + str(i)
        return res

    def has_pair(self):
        check = False
        for i in range(9):
            j = i + 1
            el1 = int(self.tableWidget.item(0, i).text())
            el2 = int(self.tableWidget.item(0, j).text())
            if el1 > 0 and el2 > 0 or el1 < 0 and el2 < 0:
                if check:
                    return True
                check = True
        return False

    def clear(self):
        self.tableWidget.clear()
        self.double_sum_label.setText("")
        self.index_label.setText("")
        self.time_no_threads_label.setText("Время работы без потоков: ")
        self.time_with_threads_label.setText("Время с потоками")

    def enter_random(self):
        if self.comboBox.currentText() == "случайно":
            for i in range(10):
                self.tableWidget.setItem(0, i, QtWidgets.QTableWidgetItem(str(random.randint(-100, 100))))
        elif self.comboBox.currentText() == "с случайной частотой":
            for i in range(10):
                if i < int(self.spinBox.text()):
                    self.tableWidget.setItem(0, i, QtWidgets.QTableWidgetItem(str(random.randint(-100, 100))))
                else:
                    s = self.tableWidget.item(0, i % int(self.spinBox.text())).text()
                    self.tableWidget.setItem(0, i, QtWidgets.QTableWidgetItem(str(s)))


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = ExampleApp()
    MainWindow.show()
    sys.exit(app.exec())
