class Progress(object):
    chars = ['|', '/', '-', '\\']
    idx = 0
    def __call__(self):
        print(self.chars[self.idx] + '\r', end ='', flush = True)
        self.idx += 1
        if self.idx > 3: self.idx = 0
        # Callable class object example as a progress indicator
