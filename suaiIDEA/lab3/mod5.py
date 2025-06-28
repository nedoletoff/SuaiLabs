import tkinter as tk
from dataclasses import dataclass
import rsa
import viziner


@dataclass
class Text:
    value_salted: tk.Text
    salt: tk.Entry
    rsa_first: tk.Entry
    rsa_second: tk.Entry

    def __init__(self):
        self.value_salted = None
        self.salt = None
        self.rsa_first = None
        self.rsa_second = None


window = tk.Tk()
window.wm_title("mod5")
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
    entrys.value_salted.pack()
    add_gap()
    label_salt.pack()
    entrys.salt.pack()
    add_gap()
    label_rsa.pack()
    entrys.rsa_first.pack()
    entrys.rsa_second.pack()
    btn_generate.pack()
    label_signature_text.pack()
    add_gap()
    label_signature.pack()
    add_gap()
    label_errors.pack()


def button_click():
    num = entrys.value_salted.get(1.0, tk.END)
    if not entrys.salt.get().isascii():
        label_errors["text"] = "Slat wrong"
        print(entrys.salt.get(), "salt")
        return

    if not num.isascii():
        label_errors["text"] = "Text wrong"
        return

    if not entrys.rsa_first.get().isdigit():
        label_errors["text"] = "First RSA wrong"
        return

    if not entrys.rsa_second.get().isdigit():
        label_errors["text"] = "Second RSA wrong"
        return
    label_errors["text"] = ""

    try:
        public = (int(entrys.rsa_first.get()), int(entrys.rsa_second.get()))
        res = viziner.decipher(num, entrys.salt.get())
        text = rsa.encrypt(public, res)

        label_signature.delete(1.0, tk.END)
        label_signature.insert(1.0, text)
    except Exception as e:
        label_errors["text"] = str(e)
        raise e


btn_generate = tk.Button(
    text="signature",
    command=button_click
)

label_num = tk.Label(
    text="Enter num",
    fg="black",
    bg="white",
    width=width_m,
)

entrys.value_salted = tk.Text(
    width=width_m,
    height=3
)

label_salt = tk.Label(
    text="Enter a salt",
    fg="black",
    bg="white",
    width=width_m,
)

entrys.salt = tk.Entry(
    width=width_m
)

label_rsa = tk.Label(
    text="Enter RSA public keys",
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

label_signature_text = tk.Label(
    text="Signature",
    fg="black",
    bg="white",
    width=width_m,
)

label_signature = tk.Text(
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
