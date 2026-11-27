#include "diamond.hpp"
#include "square.hpp"
#include <iostream>

int main()
{
  using namespace chacha;

  try
  {
    std::cout << "--- PROBANDO SQUARE (Cuadrado) ---\n";
    Square sq(5.0, {0.0, 0.0});

    std::cout << "Area: " << sq.getArea() << "\n";

    rectangle_t frameSq = sq.getFrameRect();
    std::cout << "FrameRect Ancho: " << frameSq.width << " (Posicion X: " << frameSq.pos.x << ")\n";

    sq.move(2.0, 3.0);
    std::cout << "Nueva Posicion (mover relativo): " << sq.getFrameRect().pos.x << ", " << sq.getFrameRect().pos.y
              << "\n";

    std::cout << "\n--- PROBANDO DIAMOND (Rombo) ---\n";
    Diamond dm(4.0, 6.0, {1.0, 1.0});

    std::cout << "Area: " << dm.getArea() << "\n";

    rectangle_t frameDm = dm.getFrameRect();
    std::cout << "FrameRect Ancho: " << frameDm.width << " | Alto: " << frameDm.height << "\n";

    dm.move({10.0, 10.0});
    std::cout << "Nueva Posicion (mover absoluto): " << dm.getFrameRect().pos.x << ", " << dm.getFrameRect().pos.y
              << "\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error inesperado: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
