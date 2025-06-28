import tkinter

from tkinter import *
from tkinter import filedialog
import tkinter.messagebox as mbox

from PIL import ImageTk, Image


class Paint(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)

        self.parent = parent
        self.color = "black"
        self.brush_size = 2
        self.setUI()

    def set_color(self, new_color):
        self.color = new_color

    def set_brush_size(self, new_size):
        self.brush_size = new_size

    def draw(self, event):
        self.canv.create_oval(event.x - self.brush_size,
                              event.y - self.brush_size,
                              event.x + self.brush_size,
                              event.y + self.brush_size,
                              fill=self.color, outline=self.color)

    def getpath(self, path):
        a = path.split(r'/')
        # print(a)
        fname = a[-1]
        l = len(fname)
        location = path[:-l]
        return location

    # function defined to get the folder name from which image is selected
    def get_folder_name(self, path):
        a = path.split(r'/')
        name = a[-1]
        return name

    # function defined to get the file name of image is selected
    def get_file_name(self, path):
        a = path.split(r'/')
        fname = a[-1]
        a = fname.split('.')
        a = a[0]
        return a

    # function defined to open the image file
    def open_file_name(self):
        filename = filedialog.askopenfilename(title='"pen')
        return filename

    # function defined to open the selected image
    def open_img(self):
        x = self.open_file_name()
        img = Image.open(x)
        eimg = img
        img = ImageTk.PhotoImage(img)
        temp = x
        location = getpath(temp)
        filename = get_file_name(temp)
        if panelA is None or panelB is None:
            panelA = Label(image=img)
            panelA.image = img
            panelA.pack(side="left", padx=10, pady=10)
            panelB = Label(image=img)
            panelB.image = img
            panelB.pack(side="right", padx=10, pady=10)
        else:
            panelA.configure(image=img)
            panelB.configure(image=img)
            panelA.image = img
            panelB.image = img

    # function defined to reset the edited image to original one
    def reset(self):
        image = ImageTk.PhotoImage(image)
        panelB.configure(image=image)
        panelB.image = image
        mbox.showinfo("Success", "Image reset to original format!")

    # function defined to same the edited image
    def save_img(self):
        filename = filedialog.asksaveasfile(mode='w', defaultextension=".jpg")
        if not filename:
            return
        mbox.showinfo("Success", "Edited Image Saved Successfully!")

    def setUI(self):
        self.parent.title("lab3.1")  #
        self.pack(fill=BOTH, expand=1)

        self.columnconfigure(6,
                             weight=1)  # Даем седьмому столбцу возможность растягиваться, благодаря чему кнопки не будут разъезжаться при ресайзе
        self.rowconfigure(2, weight=1)  # То же самое для третьего ряда

        self.canv = Canvas(self, bg="white")  # Создаем поле для рисования, устанавливаем белый фон
        self.canv.grid(row=2, column=0, columnspan=7,
                       padx=5, pady=5,
                       sticky=E + W + S + N)  # Прикрепляем канвас методом grid. Он будет находится в 3м ряду, первой колонке, и будет занимать 7 колонок, задаем отступы по X и Y в 5 пикселей, и заставляем растягиваться при растягивании всего окна
        self.canv.bind("<B1-Motion>",
                       self.draw)  # Привязываем обработчик к канвасу. <B1-Motion> означает "при движении зажатой левой кнопки мыши" вызывать функцию draw

        color_lab = Label(self, text="Color: ")  # Создаем метку для кнопок изменения цвета кисти
        color_lab.grid(row=0, column=0,
                       padx=6)  # Устанавливаем созданную метку в первый ряд и первую колонку, задаем горизонтальный отступ в 6 пикселей

        red_btn = Button(self, text="Red", width=10,
                         command=lambda: self.set_color(
                             "red"))  # Создание кнопки:  Установка текста кнопки, задание ширины кнопки (10 символов), функция вызываемая при нажатии кнопки.
        red_btn.grid(row=0, column=1)  # Устанавливаем кнопку

        # Создание остальных кнопок повторяет ту же логику, что и создание
        # кнопки установки красного цвета, отличаются лишь аргументы.

        green_btn = Button(self, text="Green", width=10,
                           command=lambda: self.set_color("green"))
        green_btn.grid(row=0, column=2)

        blue_btn = Button(self, text="Blue", width=10,
                          command=lambda: self.set_color("blue"))
        blue_btn.grid(row=0, column=3)

        black_btn = Button(self, text="Black", width=10,
                           command=lambda: self.set_color("black"))
        black_btn.grid(row=0, column=4)

        white_btn = Button(self, text="White", width=10,
                           command=lambda: self.set_color("white"))
        white_btn.grid(row=0, column=5)

        clear_btn = Button(self, text="Clear all", width=10,
                           command=lambda: self.canv.delete("all"))
        clear_btn.grid(row=0, column=6, sticky=W)

        size_lab = Label(self, text="Brush size: ")
        size_lab.grid(row=1, column=0, padx=5)
        one_btn = Button(self, text="Two", width=10,
                         command=lambda: self.set_brush_size(2))
        one_btn.grid(row=1, column=1)

        two_btn = Button(self, text="Five", width=10,
                         command=lambda: self.set_brush_size(5))
        two_btn.grid(row=1, column=2)

        five_btn = Button(self, text="Seven", width=10,
                          command=lambda: self.set_brush_size(7))
        five_btn.grid(row=1, column=3)

        seven_btn = Button(self, text="Ten", width=10,
                           command=lambda: self.set_brush_size(10))
        seven_btn.grid(row=1, column=4)

        ten_btn = Button(self, text="Twenty", width=10,
                         command=lambda: self.set_brush_size(20))
        ten_btn.grid(row=1, column=5)

        twenty_btn = Button(self, text="Fifty", width=10,
                            command=lambda: self.set_brush_size(50))
        twenty_btn.grid(row=1, column=6, sticky=W)

        # top label
        start1 = Label(text="Image  Editor", font=("Arial", 40), fg="magenta", underline=0)  # same way bg
        start1.place(x=350, y=10)

        # original image label
        start1 = Label(text="Original\nImage", font=("Arial", 40), fg="magenta")  # same way bg
        start1.place(x=100, y=270)

        # choose button created
        chooseb = Button(window, text="Choose", command=open_img, font=("Arial", 20))
        chooseb.place(x=30, y=20)

        # save button created
        saveb = Button(window, text="Save", command=save_img, font=("Arial", 20))

        saveb.place(x=170, y=20)

        # reset button created
        resetb = Button(window, text="Reset", command=reset, font=("Arial", 20))
        resetb.place(x=800, y=620)


def main():
    root = Tk()
    root.geometry("850x500+300+300")
    app = Paint(root)
    root.mainloop()


if __name__ == "__main__":
    main()

# defined variable
global count, emig
# global bright, con
# global frp, tname  # list of paths
frp = []
tname = []
con = 1
bright = 0
panelB = None
panelA = None





