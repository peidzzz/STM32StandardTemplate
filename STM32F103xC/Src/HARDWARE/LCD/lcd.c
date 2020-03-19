#include "lcd.h"
#include "font.h"

/************************************************************
底层函数集合
void WriteByteSPI(unsigned char byte)         // 通过SPI发送数据（1Byte）
void SPI_WriteComm(u16 CMD)                   // 通过SPI发送指令（2Bytes）
void SPI_WriteData(u16 tem_data)              // 通过SPI发送数据（2Bytes）
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)   // 选中一块区域
************************************************************/
#define LCD_SPI_CS(a)	\
						if (a)	\
						GPIOA->BSRR = GPIO_Pin_4;	\
						else		\
						GPIOA->BRR  = GPIO_Pin_4;
#define SPI_DCLK(a)	\
						if (a)	\
						GPIOA->BSRR = GPIO_Pin_5;	\
						else		\
						GPIOA->BRR  = GPIO_Pin_5;
#define SPI_SDA(a)	\
						if (a)	\
						GPIOA->BSRR = GPIO_Pin_7;	\
						else		\
						GPIOA->BRR  = GPIO_Pin_7;

void WriteByteSPI(unsigned char byte)
{
  unsigned char n;

  for (n = 0; n < 8; n++) {
    if (byte & 0x80) SPI_SDA(1)
      else SPI_SDA(0)
        byte <<= 1;

    SPI_DCLK(0);
    SPI_DCLK(1);
  }
}

void SPI_WriteComm(u16 CMD)
{
  LCD_SPI_CS(0);
  SPI_SDA(0);
  SPI_DCLK(0);
  SPI_DCLK(1);
//	LCD_WriteByteSPI(0x70);
  WriteByteSPI(CMD);

  LCD_SPI_CS(1);
}

void SPI_WriteData(u16 tem_data)
{
  LCD_SPI_CS(0);
  SPI_SDA(1);
  SPI_DCLK(0);
  SPI_DCLK(1);
//	LCD_WriteByteSPI(0x72);
  WriteByteSPI(tem_data);
  LCD_SPI_CS(1);
}

void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
  SPI_WriteComm(0x2a);
  SPI_WriteData(Xstart >> 8);
  SPI_WriteData(Xstart);
  SPI_WriteData(Xend >> 8);
  SPI_WriteData(Xend);

  SPI_WriteComm(0x2b);
  SPI_WriteData(Ystart >> 8);
  SPI_WriteData(Ystart);
  SPI_WriteData(Yend >> 8);
  SPI_WriteData(Yend);

  SPI_WriteComm(0x2c);
}

/************************************************************
中层函数集合
void DrawPixel(u16 x, u16 y, int Color)              // 在指定坐标画点
void DrawHLine(u16 x, u16 y, u16 lenth, u16 color)   // 在指定坐标画一条横线
void DrawRLine(u16 x, u16 y, u16 lenth, u16 color)   // 在指定坐标画一条竖线
void LCD_Clear(u16 Color)                            // 清屏
************************************************************/
void DrawPixel(u16 x, u16 y, int Color)
{
  BlockWrite(x, x, y, y);

  SPI_WriteData(Color >> 8);
  SPI_WriteData(Color);
}

void DrawHLine(u16 x, u16 y, u16 lenth, u16 color)
{
  for ( ; x < lenth; x++) {
    DrawPixel(x, y, color);
  }
}

void DrawRLine(u16 x, u16 y, u16 lenth, u16 color)
{
  for ( ; y < lenth; y++) {
    DrawPixel(x, y, color);
  }
}

/************************************************************
上层函数集合
void LCD_Init(void)
void LCD_Clear(u16 Color)
void LCD_Fill(u16 xStart, u16 yStart, u16 xLong, u16 yLong, u16 Color)
void LCD_Draw_Circle(u16 x0, u16 y0, u8 r);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u16 charColor, u16 bkColor)
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p, u16 charColor, u16 bkColor)
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size, u16 charColor, u16 bkColor)
************************************************************/
void LCD_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LCD_Clear(u16 Color)
{
  LCD_Fill(0, 0, 480, 320, Color);
}

void LCD_Fill(u16 xStart, u16 yStart, u16 xLong, u16 yLong, u16 Color)
{
  u32 temp;

  BlockWrite(xStart, xStart + xLong - 1, yStart, yStart + yLong - 1);

  for (temp = 0; temp < xLong * yLong; temp++) {
    SPI_WriteData(Color >> 8);
    SPI_WriteData(Color);
  }
}

void LCD_DrawCircle(u16 cx, u16 cy, u16 r, u16 color, u8 fill)
{
  u16 x, y;
  s16 delta, tmp;
  x = 0;
  y = r;
  delta = 3 - (r << 1);
  while (y > x) {
    if (fill) {
      DrawHLine(cx - x, cy + y, cx + x, color);
      DrawHLine(cx - x, cy - y, cx + x, color);
      DrawHLine(cx - y, cy + x, cx + y, color);
      DrawHLine(cx - y, cy - x, cx + y, color);
    } else {
      DrawPixel(cx + x, cy + y, color);
      DrawPixel(cx - x, cy + y, color);
      DrawPixel(cx + x, cy - y, color);
      DrawPixel(cx - x, cy - y, color);
      DrawPixel(cx + y, cy + x, color);
      DrawPixel(cx - y, cy + x, color);
      DrawPixel(cx + y, cy - x, color);
      DrawPixel(cx - y, cy - x, color);
    }
    x++;
    if (delta >= 0) {
      y--;
      tmp = (x << 2);
      tmp -= (y << 2);
      delta += (tmp + 10);
    } else {
      delta += ((x << 2) + 6);
    }
  }
}

void LCD_DrawRectangle(u16 x1, u16 y1, u16 xlong, u16 ylong, u16 Color, u8 Fill){
  if (Fill) {
    LCD_Fill(x1, y1, xlong, ylong, Color);
  } else {
    DrawHLine(x1, y1, x1 + xlong, Color);
    DrawHLine(x1, y1 + ylong, x1 + xlong, Color);
    DrawRLine(x1, y1, y1 + ylong, Color);
    DrawRLine(x1 + xlong, y1, y1 + ylong, Color);
  }
}

void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u16 charColor, u16 bkColor){
  u8 temp, t1, t;
  u16 y0 = y;
  u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);		//得到字体一个字符对应点阵集所占的字节数
  num = num - ' '; //得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
  for (t = 0; t < csize; t++) {
    if (size == 12)temp = asc2_1206[num][t]; 	 	//调用1206字体
    else if (size == 16)temp = asc2_1608[num][t];	//调用1608字体
    else if (size == 24)temp = asc2_2412[num][t];	//调用2412字体
    else return;								//没有的字库
    for (t1 = 0; t1 < 8; t1++) {
      if (temp & 0x80)DrawPixel(x, y, charColor);
      else if (1)DrawPixel(x, y, bkColor);
      temp <<= 1;
      y++;
      if (y >= 320)return;		//超区域了
      if ((y - y0) == size) {
        y = y0;
        x++;
        if (x >= 480)return;	//超区域了
        break;
      }
    }
  }
}

void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p, u16 charColor, u16 bkColor)
{
  u8 x0 = x;
  width += x;
  height += y;
  while ((*p <= '~') && (*p >= ' ')) { //判断是不是非法字符!
    if (x >= width) {
      x = x0;
      y += size;
    }
    if (y >= height)break; //退出
    LCD_ShowChar(x, y, *p, size, charColor, bkColor);
    x += size / 2;
    p++;
  }
}

u32 LCD_Pow(u8 m, u8 n)
{
  u32 result = 1;
  while (n--)result *= m;
  return result;
}

void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size, u16 charColor, u16 bkColor)
{
  u8 t, temp;
  u8 enshow = 0;
  for (t = 0; t < len; t++) {
    temp = (num / LCD_Pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1)) {
      if (temp == 0) {
        LCD_ShowChar(x + (size / 2)*t, y, ' ', size, charColor, bkColor);
        continue;
      } else enshow = 1;

    }
    LCD_ShowChar(x + (size / 2)*t, y, temp + '0', size, charColor, bkColor);
  }
}
