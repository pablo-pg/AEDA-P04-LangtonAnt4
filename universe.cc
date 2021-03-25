  /**
 * @file universe.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.2
 * @date 2021-03-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "./universe.h"

Universe::Universe() {}


Universe::Universe(World& world, const WorldType& type,
          const std::deque<Ant>& ants) {
  world_ = &world;
  steps_ = world_->GetSteps();
  ant_list_ = ants;
  infinity_ = type;
  cells_ = world_->GetMatrix();
  int paint_mode;
  bool chosen_mode = false;
  while (!chosen_mode) {
    std::cout << "A la hora de imprimir, ¿quiere usar los caracteres "
              << "pedidos (1) u otros elegidos por el desarrollador(2)?  ";
    std::cin >> paint_mode;
    if (paint_mode == 1 || paint_mode == 2) {
      chosen_mode = true;
    }
  }
  for (size_t i{0}; i < ant_list_.size(); ++i) {
    ant_list_.at(i).SetTypeWorld(type);
  }
  Simulate(paint_mode);
}


void Universe::Simulate(const int& paint_mode) {
  for (uint i {0}; i < steps_; ++i) {
    int north_count = 0;
    // system("clear");
    if (paint_mode == 1) {
      StandardPaint(i);
    } else {
      Paint(i);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    for (size_t i{0}; i < ant_list_.size(); ++i) {
      ant_list_.at(i).SetPrevMatrix(cells_);
      ant_list_.at(i).Move();
      cells_ = ant_list_.at(i).GetCell();
      for (size_t j{0}; j < ant_list_.size(); ++j) {
        ant_list_.at(j).SetMatrix(cells_);
      }
      world_->UpdateMatrix(cells_);
      world_->UpdateAntPos(ant_list_.at(i).GetHPos(),
                           ant_list_.at(i).GetVPos());
    }
  }
}


void Universe::StandardPaint(const uint& step) {
  for (size_t i {0}; i < ant_list_.size(); ++i) {
    std::cout << "Hormiga " << i + 1 << " en ("
      << static_cast<int>(ant_list_.at(i).GetHInfLimit() + ant_list_.at(i).GetHPos())
      << ", "
      << static_cast<int>(ant_list_.at(i).GetVInfLimit() + ant_list_.at(i).GetVPos())
      << ")" << std::endl;
  }
  std::cout << "Paso: " << step + 1 << std::endl;
  uint init_i = cells_.at(0).size() - 1;
  for (uint i {init_i}; i > 0; --i) {
    for (uint j {0}; j < cells_.size(); ++j) {
      KnowAnt is_ant = AreAnts(j, i);
      if (is_ant.is == true) {
        if (ant_list_.at(is_ant.list_pos).GetDirection() == up) {
          std::cout << "A";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == left) {
          std::cout << "I";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == down) {
          std::cout << "B";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == right) {
          std::cout << "D";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == rightUp) {
          std::cout << "R";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == leftUp) {
          std::cout << "Q";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == downLeft) {
          std::cout << "J";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == downRight) {
          std::cout << "C";
        }
      } else {
        if (cells_.at(j).at(i) == black) {
          std::cout << " ";
        } else {
          std::cout << "X";
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


void Universe::Paint(const uint& step) {
  for (size_t i {0}; i < ant_list_.size(); ++i) {
    std::cout << "Hormiga " << i + 1 << " en ("
      << static_cast<int>(ant_list_.at(i).GetHInfLimit() + ant_list_.at(i).GetHPos())
      << ", "
      << static_cast<int>(ant_list_.at(i).GetVInfLimit() + ant_list_.at(i).GetVPos())
      << ")" << std::setw(40) << "Paso: " << step + 1 << std::endl
      << std::endl;
  }
  std::cout << "\u2554";
  for (uint i {0}; i < cells_.size(); ++i) {
    std::cout << "\u2550";
  }
  std::cout << "\u2557" << std::endl;
  uint init_i = cells_.at(0).size() - 1;
  for (uint i {init_i}; i > 0; --i) {
    std::cout << "\u2551";
    for (uint j {0}; j < cells_.size(); ++j) {
      KnowAnt is_ant = AreAnts(j, i);
      if (is_ant.is == true) {
        if (ant_list_.at(is_ant.list_pos).GetDirection() == up) {
          std::cout << "\u2191";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == left) {
          std::cout << "\u2190";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == down) {
          std::cout << "\u2193";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == right) {
          std::cout << "\u2192";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == rightUp) {
          std::cout << "\u2197";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == leftUp) {
          std::cout << "\u2196";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == downLeft) {
          std::cout << "\u2199";
        } else if (ant_list_.at(is_ant.list_pos).GetDirection() == downRight) {
          std::cout << "\u2198";
        }
      } else {
        if (cells_.at(j).at(i) == black) {
          std::cout << " ";
        } else {
          std::cout << "\u2598";
        }
      }
    }
    std::cout << "\u2551" << std::endl;
  }
  std::cout << "\u255A";
  for (uint i {0}; i < cells_.size(); ++i) {
    std::cout << "\u2550";
  }
  std::cout << "\u255D" << std::endl;
  std::cout << std::endl;
}


KnowAnt Universe::AreAnts(const uint& x, const uint& y) {
  KnowAnt info;
  info.is = false;
  for (int i{0}; i < ant_list_.size(); ++i) {
    if (ant_list_.at(i).GetHPos() == x) {
      if (ant_list_.at(i).GetVPos() == y) {
        info.is = true;
        info.direction = ant_list_.at(i).GetDirection();
        info.h_pos = x;
        info.v_pos = y;
        info.list_pos = i;
      }
    }
  }
  return info;
}



