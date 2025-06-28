import logging

from PyQt6 import QtWidgets
import sys
import viginer_v
import viginer

logging.basicConfig(
    filename="/home/nedoletoff/Documents/tp/sample.log",
    format='%(asctime)s %(levelname)s %(message)s',
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S'
)
log = logging.getLogger("ex")


class ExampleApp(QtWidgets.QMainWindow, viginer_v.Ui_MainWindow):
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.cipher_button.clicked.connect(self.cipher)
        self.decipher_button.clicked.connect(self.decipher)

    def cipher(self):
        try:
            text = self.text_edit.toPlainText()
            if len(text) == 0:
                raise Exception("Text field is empty")
            key = self.key_word_cipher_edit.toPlainText()
            if len(key) == 0:
                raise Exception("Key word field is empty")
            res = viginer.cipher(text, key)
            self.result_cipher_browser.setText(res)
        except Exception as e:
            log.exception(e)
            self.error_label.setText(str(e))
        else:
            self.error_label.setText("")

    def decipher(self):
        try:
            text = self.cipher_text_edit.toPlainText()
            if len(text) == 0:
                raise Exception("Text field is empty")
            key = self.key_word_decipher_edit.toPlainText()
            if len(key) == 0:
                raise Exception("Key word field is empty")
            res = viginer.decipher(text, key)
            self.result_decipher_browser.setText(res)
        except Exception as e:
            log.exception(e)
            self.error_label.setText(str(e))
        else:
            self.error_label.setText("")


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = ExampleApp()
    window.show()
    app.exec()


if __name__ == '__main__':
    main()
