
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
i = 0

for y in xrange(image.get_size()[1]):
	for x in xrange(image.get_size()[0]):
		val = image.get_at((x, y))
		
		s = s + str(val[0]) + ','
		i += 1

print s
print i

while 1:
	window.blit(image, (0, 0))
	pygame.display.flip()
	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()
