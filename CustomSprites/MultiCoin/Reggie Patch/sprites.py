class SpriteImage_MultiCoin(SLib.SpriteImage_StaticMultiple):
    def __init__(self, parent):
        super().__init__(parent, 1)
        self.offset = (-16, -16)

    def loadImages():
        for i in range(4): # type
            ImageCache[f'MultiCoin{i}'] = SLib.GetImage(f'MultiCoin{i}.png')

    def dataChanged(self):
        type = ((self.parent.spritedata[2] & 0xF0) >> 4) % 4

        self.scale = 1.5

        if type == 1:
            self.offset = (-24, -24)

        self.image = ImageCache[f'MultiCoin{type}']

        super().dataChanged()

# make sure you also remember to assign this image to your sprite ID at the very bottom of the file!