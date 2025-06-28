import tkinter as tk
import rsa

window = tk.Tk()
width_m = 50
window.wm_title("mod1")


def add_gap():
    label_gap = tk.Label(
        height=1,
        width=width_m
    )
    label_gap.pack()


def convert():
    add_gap()
    label_first_num.pack()
    first_entry.pack()
    add_gap()
    label_second_num.pack()
    second_entry.pack()
    btn_generate.pack()
    label_public_keys_text.pack()
    add_gap()
    label_public_keys.pack()
    add_gap()
    label_private_keys_text.pack()
    add_gap()
    label_private_keys.pack()
    label_errors.pack()

def button_click():
    if not first_entry.get().isdigit():
        label_errors["text"] = "First num is not num"
        return
    if not rsa.is_prime(int(first_entry.get())):
        label_errors["text"] = "First num is not prime num"
        return

    if not second_entry.get().isdigit():
        label_errors["text"] = "Second num is not num"
        return
    if not rsa.is_prime(int(second_entry.get())):
        label_errors["text"] = "Second num is not prime num"
        return
    label_errors["text"] = ""

    try:
        public, private = rsa.generate_key_pair(int(first_entry.get()), int(second_entry.get()))
        label_public_keys.delete(1.0, tk.END)
        label_private_keys.delete(1.0, tk.END)
        label_public_keys.insert(1.0, str(public))
        label_private_keys.insert(1.0, str(private))
    except Exception as e:
        label_errors["text"] = str(e)


btn_generate = tk.Button(
    text="generate keys",
    command=button_click
)

label_first_num = tk.Label(
    text="Enter a prime number",
    fg="black",
    bg="white",
    width=width_m,
)

first_entry = tk.Entry(
    width=width_m
)

label_second_num = tk.Label(
    text="Enter a prime number",
    fg="black",
    bg="white",
    width=width_m,
)

second_entry = tk.Entry(
    width=width_m
)

label_public_keys_text = tk.Label(
    text="Public keys",
    fg="black",
    bg="white",
    width=width_m,
)

label_public_keys = tk.Text(
    height=1,
    fg="black",
    bg="white",
    width=width_m
)

label_private_keys_text = tk.Label(
    text="Private keys",
    fg="black",
    bg="white",
    width=width_m,
)

label_private_keys = tk.Text(
    height=1,
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
