#pragma once
#include <string>

class Texture2D {
private:
  unsigned int rendererID;
  std::string filePath;
  unsigned char *localBuffer;
  int width;
  int height;
  int bpp;

public:
  Texture2D();
  ~Texture2D();

  void init(const std::string &path);

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidth() const { return width; }
  inline int getHeight() const { return height; }
};
