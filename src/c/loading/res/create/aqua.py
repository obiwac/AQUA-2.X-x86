
import sys

import pygame
from pygame.locals import *

pygame.init()

image = pygame.image.load("aqua.png")

window = pygame.display.set_mode(image.get_size())
pygame.display.set_caption("AQUA")

def terminate():
	pygame.quit()
	sys.exit()

s = ""

for y in xrange(image.get_size()[1]):
	for x in xrange(image.get_size()[0]):
		val = image.get_at((x, y))[0]
		s = s + str((val << 16) | (val << 8) | val) + ','

print s

while 1:
	window.blit(image, (0, 0))
	pygame.display.flip()
	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()
