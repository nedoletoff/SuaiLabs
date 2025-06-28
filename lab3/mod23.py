import tkinter as tk
from dataclasses import dataclass
import rsa
import viziner


@dataclass
class Text:
    value: tk.Entry
    salt: tk.Entry
    rsa_first: tk.Entry
    rsa_second: tk.Entry

    def __init__(self):
        self.salt = None
        self.value = None
        self.rsa_first = None
        self.rsa_second = None


window = tk.Tk()
window.wm_title("mod23")
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
    entrys.value.pack()
    add_gap()
    label_salt.pack()
    entrys.salt.pack()
    add_gap()
    label_rsa.pack()
    entrys.rsa_first.pack()
    entrys.rsa_second.pack()
    btn_generate.pack()
    label_num_with_salt_cipher_text.pack()
    add_gap()
    label_num_with_salt_cipher.pack()
    add_gap()
    label_errors.pack()


def button_click():
    if not entrys.value.get().isascii():
        label_errors["text"] = "Text wrong"
        return

    if not entrys.salt.get().isascii():
        label_errors["text"] = "Slat wrong"
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
        salt = entrys.salt.get()
        text = entrys.value.get()
        temp = viziner.cipher(text, salt)
        label_num_with_salt_cipher.delete(1.0, tk.END)
        label_num_with_salt_cipher.insert(1.0, rsa.encrypt(public, temp))
    except Exception as e:
        label_errors["text"] = str(e)


btn_generate = tk.Button(
    text="cipher",
    command=button_click
)

label_num = tk.Label(
    text="Enter num",
    fg="black",
    bg="white",
    width=width_m,
)

entrys.value = tk.Entry(
    width=width_m
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

label_num_with_salt_cipher_text = tk.Label(
    text="Num with salt cipher",
    fg="black",
    bg="white",
    width=width_m,
)

label_num_with_salt_cipher = tk.Text(
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
