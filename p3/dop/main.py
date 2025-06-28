import logging
import math
import tkinter
from tkinter import messagebox
from tkinter import *

logging.basicConfig(
    filename="/home/nedoletoff/Documents/tp/sample.log",
    format='%(asctime)s %(levelname)s %(message)s',
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S'
)
log = logging.getLogger("ex")

width_m = 50
label_num = tkinter.Label(
    text="Enter deep",
    fg="black",
    bg="white",
    width=width_m,
)

value = tkinter.Entry(
    width=width_m
)


def draw_trees():
    x = 600
    y = 650
    side = 100
    deep = value.get()
    print("started")
    try:
        int(deep)
        deep = int(deep)
    except Exception as e:
        log.exception(e)
        messagebox.showerror("Error", str(e))
        deep = 11
    alfa = math.pi / 3
    draw_tree(x / 2 - 100, y - 100, side, math.pi / 2, alfa * 3 / 4, deep, 1)
    draw_tree(x + 100, y + 100, side, math.pi / 2, alfa, deep, 1)
    draw_tree(x + 900, y * 3 / 4 + 100, side, math.pi / 2, alfa / 2, deep, 1)


button = tkinter.Button(
    text="start",
    command=draw_trees
)


def draw_tree(x, y, side, fi, alfa, deep, count_deep):
    global canv
    x1 = x
    y1 = y
    dx = side * math.sin(fi)
    dy = side * math.cos(fi)
    x2 = x + dx
    y2 = y - dy
    x3 = x + dx - dy
    y3 = y - dy - dx
    x4 = x - dy
    y4 = y - dx
    x5 = x - dy + side * math.cos(alfa) * math.sin(fi - alfa)
    y5 = y - dx - side * math.cos(alfa) * math.cos(fi - alfa)

    if count_deep < 5:
        colour = "#" + str(count_deep * 20) + "0000"
    elif count_deep < 9:
        colour = "#00" + str(count_deep * 10) + "00"
    else:
        colour = "#009900"
    canv.create_polygon(x1, y1, x2, y2, x3, y3, x4, y4, fill=colour)
    canv.create_polygon(x4, y4, x3, y3, x5, y5, fill=colour)
    if deep > 1:
        draw_tree(x5, y5, side * math.sin(alfa), fi - alfa + math.pi / 2, alfa, deep - 1, count_deep + 1)
        draw_tree(x4, y4, side * math.cos(alfa), fi - alfa, alfa, deep - 1, count_deep + 1)


def main():
    global canv, root
    root = Tk()
    root.title("Pifagor's tree")
    root.bind('<Control-z>', exit_)
    label_num.pack()
    value.pack()
    button.pack()
    canv = Canvas(root, width=1800, height=1200, bg="lightblue")
    canv.pack()

    canv.create_rectangle(0, 1200, 1800, 550, fill="#ADFF2F")
    root.mainloop()


def exit_(event):
    root.destroy()


if __name__ == "__main__":
    main()
