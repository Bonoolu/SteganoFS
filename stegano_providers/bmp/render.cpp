#include "render.h"

void Render::draw(const CanvasMono &canvasMono) {
  for (size_t y = 0; y < canvasMono.getSizeY(); y++) {
	for (size_t x = 0; x < canvasMono.getSizeX(); x++) {
	  std::cout << ((canvasMono.getPixel(Vector2D{x, y}).isSet) ? " X" : " .");
	}
	std::cout << std::endl;
  }
}

uint32_t Render::drawBmp(const CanvasRGB &canvasRGB, FILE *bmpFile) {
  size_t padding = ((4 - ((canvasRGB.getSizeX()*3) % 4)) % 4);

  unsigned char const bfType[2] = {0x42, 0x4D}; // BM
  auto const bfSize = static_cast<uint32_t>(54 + ((canvasRGB.getSizeX() * canvasRGB.getSizeY() * 3) + (canvasRGB.getSizeY() * padding)));
  uint32_t const bfReserved = 0;
  uint32_t const bfOffBits = 54;
  int32_t const biSize = 40;
  auto const biWidth = static_cast<int32_t>(canvasRGB.getSizeX());
  auto const biHeight = static_cast<int32_t>(canvasRGB.getSizeY());
  uint16_t const biPlane = 1;
  uint16_t const biBitCount = 24;
  uint32_t const biCompression = 0;
  uint32_t const biSizeImage = 0;
  int32_t const biXPelsPerMeter = 0;
  int32_t const biYPelsPerMeter = 0;
  uint32_t const biClrUsed = 0;
  uint32_t const biClrImportant = 0;

  fwrite(bfType, sizeof(unsigned char), sizeof(bfType), bmpFile);
  fwrite(&bfSize, sizeof(uint32_t), 1, bmpFile);
  fwrite(&bfReserved, sizeof(uint32_t), 1, bmpFile);
  fwrite(&bfOffBits, sizeof(uint32_t), 1, bmpFile);

  fwrite(&biSize, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biWidth, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biHeight, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biPlane, sizeof(uint16_t), 1, bmpFile);
  fwrite(&biBitCount, sizeof(uint16_t), 1, bmpFile);biSizeImage
  fwrite(&biCompression, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biSizeImage, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biXPelsPerMeter, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biYPelsPerMeter, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biClrUsed, sizeof(uint32_t), 1, bmpFile);
  fwrite(&biClrImportant, sizeof(uint32_t), 1, bmpFile);

  for (size_t y = canvasRGB.getSizeY(); y > 0; y--) {
	for (size_t x = 0; x < canvasRGB.getSizeX(); x++) {

	  unsigned char const b = canvasRGB.getPixel(Vector2D{x, y - 1}).b;
	  unsigned char const g = canvasRGB.getPixel(Vector2D{x, y - 1}).g;
	  unsigned char const r = canvasRGB.getPixel(Vector2D{x, y - 1}).r;

	  fwrite(&b, sizeof(unsigned char), sizeof(b), bmpFile);
	  fwrite(&g, sizeof(unsigned char), sizeof(g), bmpFile);
	  fwrite(&r, sizeof(unsigned char), sizeof(r), bmpFile);
	}
	for (size_t i = 0; i < padding; i++) {
	  static unsigned char pad = 0x00;
	  fwrite(&pad, sizeof(unsigned char), sizeof(pad), bmpFile);
	}
  }

  return bfSize;
}

uint32_t Render::drawGif(const CanvasRGB **canvas, size_t size_Canvas, FILE *bmpFile, Pixel *colorTale, size_t size_Colortable) {
  CanvasRGB const &canvasRGB = **canvas;

  // Header
  unsigned char const header[6] = {'G', 'I', 'F', '8', '9', 'a'};

  // Logical Screen Descriptor
  uint16_t const biWidth = canvasRGB.getSizeX();
  uint16_t const biHeight = canvasRGB.getSizeY();
  unsigned char const packedField = 0b10010001;
  unsigned char const backgroundColorIndex = 0x00;
  unsigned char const pixelAspectRatio = 0x00;

  // Global Color Table
  unsigned char const red[3] = {0xFF, 0x00, 0x00};
  unsigned char const black[3] = {0x00, 0x00, 0x00};
  unsigned char const blue[3] = {0x00, 0x00, 0xFF};
  unsigned char const green[3] = {0x00, 0x00, 0x00};

  // Graphics Control Extension
  //none

  // Image Descriptor
  unsigned char const imageSeperator = ',';
  unsigned char const imageLeft = 0x00;
  unsigned char const imageTop = 0x00;
  uint16_t const imageWidth = canvasRGB.getSizeX();
  uint16_t const imageHeight = canvasRGB.getSizeY();
  unsigned char const imagePackedField = 0b00000000;

  // Local Color Table
  //none


  return 0; //TODO!
}