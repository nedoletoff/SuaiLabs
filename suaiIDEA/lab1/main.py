import ctypes


class IDEA(object):
    IDEAKEYSIZE = 16
    IDEABLOCKSIZE = 8
    IDEAROUNDS = 8
    IDEAKEYLEN = 6 * IDEAROUNDS + 4

    @staticmethod
    def pr():
        print(IDEA.IDEAKEYSIZE, " ",
              IDEA.IDEAROUNDS, " ",
              IDEA.IDEAKEYLEN, " ",
              IDEA.IDEAKEYLEN)


dll = ctypes.cdll.LoadLibrary(r".\library.dll")
dll.get_text()
