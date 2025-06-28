import tkinter as tk
from dataclasses import dataclass
import rsa
import viziner


@dataclass
class Text:
    signature: tk.Text
    rsa_first: tk.Entry
    rsa_second: tk.Entry

    def __init__(self):
        self.signature = None
        self.rsa_first = None
        self.rsa_second = None


window = tk.Tk()
window.wm_title("mod7")
width_m = 50
entrys = Text()


def add_gap():
    label_gap = tk.Label(
        height=1,
        width=width_m
    )
    label_gap.pack()


def convert():
    add_gap()
    label_num.pack()
    entrys.signature.pack()
    add_gap()
    label_rsa.pack()
    entrys.rsa_first.pack()
    entrys.rsa_second.pack()
    btn_generate.pack()
    label_result_text.pack()
    add_gap()
    label_result.pack()
    add_gap()
    label_errors.pack()


def button_click():
    num = entrys.signature.get(1.0, tk.END).split('\n')[0]
    num = num.split()
    for i, el in enumerate(num):
        if not el.isdigit():
            label_errors["text"] = "Signature string wrong"
            return
        else:
            num[i] = int(el)

    if not entrys.rsa_first.get().isdigit():
        label_errors["text"] = "First RSA wrong"
        return

    if not entrys.rsa_second.get().isdigit():
        label_errors["text"] = "Second RSA wrong"
        return
    label_errors["text"] = ""

    try:
        private = (int(entrys.rsa_first.get()), int(entrys.rsa_second.get()))

        label_result.delete(1.0, tk.END)
        label_result.insert(1.0, rsa.decrypt(private, num))
    except Exception as e:
        label_errors["text"] = str(e)


btn_generate = tk.Button(
    text="check",
    command=button_click
)

label_num = tk.Label(
    text="Enter signature",
    fg="black",
    bg="white",
    width=width_m,
)

entrys.signature = tk.Text(
    width=width_m,
    height=3
)

label_rsa = tk.Label(
    text="Enter RSA private keys",
    fg="black",
    bg="white",
    width=width_m,
)

entrys.rsa_first = tk.Entry(
    width=width_m
)

entrys.rsa_second = tk.Entry(
    width=width_m
)

label_result_text = tk.Label(
    text="Result",
    fg="black",
    bg="white",
    width=width_m,
)

label_result = tk.Text(
    height=5,
    fg="black",
    bg="white",
    width=width_m
)

label_errors = tk.Label(
    height=1,
    width=width_m
)

convert()
window.mainloop()
