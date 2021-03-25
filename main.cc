  /**
 * @file main.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.3
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <iostream>

#include "./universe.h"

int start_menu();
World* InfinitMenu();
World* FinitMenu();
std::deque<Ant*> AntMenu(World* world);


int main() {
  try {
    start_menu();
  }
  catch (std::bad_alloc &e) {
    std::cerr << "langton's ant: " << e.what() << " (ha introducido un"
              << " tamaño o un número de pasos negativo)." << '\n';
    return 2;
  }
  catch(std::system_error& e) {
    std::cerr << "langton's ant: " << e.what() << '\n';
    return 2;
  }
  // catch (...) {
  //   std::cerr << "Error desconocido" << std::endl;
  // }
  return 0;
}


int start_menu() {
  system("clear");
  bool selected = 0;
  WorldType type;
  World* world;
  while (selected == 0) {
    std::cout << "Bienvenido a mi versión de la hormiga de Langton"
              << std::endl << "Quiere una malla infinita (0) o finita (1)?"
              << " \"q\" para salir  ";
    std::string mode;
    std::cin >> mode;
    if (mode == "0") {                    /// MUNDO INFINITO
      selected = 1;
      type = infinity_world;
      world = InfinitMenu();
    } else if (mode == "1") {             /// MUNDO FINITO
      selected = 1;
      type = finit_world;
      world = FinitMenu();
    } else if (mode == "q") {
      selected = 1;
      return 0;
    } else {
      std::cout << "No ha elegido una opción correcta" << std::endl;
    }
  }
  std::deque<Ant*> ants;
  ants = AntMenu(world);
  Universe(*world, type, ants);
  return 0;
}


World* InfinitMenu() {
  std::cout << "-------------------------Mundo Infinito-----------------------"
            << std::endl;
  std::cout << "Si quiere una malla cuadrada introduca \"1\", si la quiere"
            << " rectangular \"2\" y si la quiere cuadrada a la vista \"3\""
            << " (q para salir): ";
  std::string shape;
  std::cin >> shape;
  World* world;
  int steps;
  /// Malla cuadrada
  if (shape == "1") {
    std::cout << "Introduzca el tamaño: ";
    uint size;
    std::cin >> size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new InfinityWorld();
    world->SetSteps(steps);
    world->SetSize(size + 1, size + 1);
  /// Malla rectangular
  } else if (shape == "2") {
    std::cout << "Introduzca el tamaño horizontal: ";
    uint h_size;
    std::cin >> h_size;
    std::cout << "Introduzca el tamaño vertical: ";
    uint v_size;
    std::cin >> v_size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new InfinityWorld();
    world->SetSteps(steps);
    world->SetSize(h_size + 1, v_size + 1);
    int paint_mode;
  } else if (shape == "3") {
    std::cout << "Introduzca el tamaño: ";
    uint size;
    std::cin >> size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new InfinityWorld();
    world->SetSteps(steps);
    world->SetSize(2 * size  + 1, size + 1);
  } else if (shape == "q") {
    return 0;
  } else {
    std::cout << "No ha introducido una opción correcta." << std::endl;
  }
  return world;
}


World* FinitMenu() {
  std::cout << "-------------------------Mundo Finito-----------------------"
            << std::endl;
  std::cout << "Si quiere una malla cuadrada introduca \"1\", si la quiere"
            << " rectangular \"2\" y si la quiere cuadrada a la vista \"3\""
            << " (q para salir): ";
  std::string shape;
  std::cin >> shape;
  int steps;
  World* world;
  /// Malla cuadrada
  if (shape == "1") {
    std::cout << "Introduzca el tamaño: ";
    uint size;
    std::cin >> size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new FinitWorld();
    world->SetSteps(steps);
    world->SetSize(size + 1, size + 1);
  /// Malla rectangular
  } else if (shape == "2") {
    std::cout << "Introduzca el tamaño horizontal: ";
    uint h_size;
    std::cin >> h_size;
    std::cout << "Introduzca el tamaño vertical: ";
    uint v_size;
    std::cin >> v_size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new FinitWorld();
    world->SetSteps(steps);
    world->SetSize(h_size + 1, v_size + 1);
    int paint_mode;
  } else if (shape == "3") {
    std::cout << "Introduzca el tamaño: ";
    uint size;
    std::cin >> size;
    std::cout << "Introduzca el número de pasos a simular: ";
    std::cin >> steps;
    std::cout << std::endl;
    world = new FinitWorld();
    world->SetSteps(steps);
    world->SetSize(2 * size + 1, size + 1);
  } else if (shape == "q") {
    return 0;
  } else {
    std::cout << "No ha introducido una opción correcta." << std::endl;
  }
  return world;
}


std::deque<Ant*> AntMenu(World* world) {
  bool good_num = 0;
  std::deque<Ant*> ants;
  int ants_num;
  while (good_num == 0) {
    std::cout << std::endl << "Introduzca el número de hormigas que desea: ";
    std::cin >> ants_num;
    if (ants_num <= 0) {
      std::cout << "no puede haber 0 o menos hormigas" << std::endl;
    } else {
      good_num = 1;
    }
  }
  std::map<std::string, Directions> mapped_directions;
  mapped_directions["up"] = up;
  mapped_directions["down"] = down;
  mapped_directions["left"] = left;
  mapped_directions["right"] = right;
  mapped_directions["leftUp"] = leftUp;
  mapped_directions["rightUp"] = rightUp;
  mapped_directions["downLeft"] = downLeft;
  mapped_directions["downRight"] = downRight;
  for (size_t i {0}; i < ants_num; ++i) {
    std::cout << "Introduzca la posición en X de la hormiga (desde "
              << "-" << world->GetMatrix().size() / 2 << " hasta "
              << world->GetMatrix().size() / 2 - 1 << "): ";
    int x_pos;
    std::cin >> x_pos;
    std::cout << "Introduzca la posición en Y de la hormiga (desde "
              << "-" << world->GetMatrix().at(0).size() / 2 << " hasta "
              << world->GetMatrix().at(0).size() / 2 - 1 << "): ";
    int y_pos;
    std::cin >> y_pos;
    std::cout << "Introduzca la dirección de la hormiga (up, down, left, right,"
              << " leftUp, rightUp, downRight, downLeft): ";
    std::string dir;
    std::cin >> dir;
    Ant* new_ant;
    new_ant = new Ant_A();
    new_ant->SetData(x_pos, y_pos, mapped_directions[dir], world->GetMatrix());
    ants.push_back(new_ant);
  }
  return ants;
}


