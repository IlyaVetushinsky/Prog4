#include <iostream>
#include "..\..\Prog4\Prog4\Prog4h.h"
using namespace Prog4;

int main() {
	Space S;
	std::cout << "Empty constructor done" << std::endl;
	S.print(std::cout);
	S.add_object(2, { 5,5 }, 0, 0, 0, 0);
	S.add_object(3, { 0,0 }, 0, 0, 0, 0);
	S.add_object(1, { 2,2 }, 0, 0, 0, 0);
	std::cout << "Objects added" << std::endl;
	S.print(std::cout);
	S.reset_Size({ 15,10 });
	std::cout << "Space resized" << std::endl;
	S.print(std::cout);
	std::cout << "Space resized" << std::endl;
	S.reset_Size({ 5,10 });
	S.print(std::cout);
	std::cout << "Create your Space!" << std::endl;
	Cordinate c = input_c();
	Space S1(c);
	std::cout << S1.get_Size().x << std::endl << S1.get_Size().y << std::endl << std::endl;
	S1.print(std::cout);
	Cell* cell = nullptr;
	Platform* platform = nullptr;
	Static_Platform* static_platform = nullptr;
	Mobile_Platform* mobile_platform = nullptr;
	Module* module = nullptr;
	int rc;
	while (rc = dialog(msgs1, NMsgs1)) {
		if (rc == 1) {
			std::cout << "Input cordinate of new object" << std::endl;
			Cordinate c = input_c();
			int t;
			std::cout << "Input type of object : 0-empty cell, 1-barrier, 2- static platform, 3-mobile platform, 4-enemy" << std::endl;
			while (getNum(t) < 0 || t < 0 || t > 4)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			int les = 0;
			int ns = 0;
			int v = 1;
			if (t == 2 || t == 3) {
				std::cout << "Input level energy supply" << std::endl;
				while (getNum(les) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				std::cout << "Input count of slots" << std::endl;
				while (getNum(ns) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (t == 3) {
					std::cout << "Input speed" << std::endl;
					while (getNum(v) < 0)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
				}
			}
			if (S1.add_object(t, c, 0, v, les, ns)) {
				std::cout << "This cell is busy. If you want to add anyway put 1" << std::endl;
				int r;
				while (getNum(r) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (r == 1)
					S1.add_object(t, c, 1, les, ns, v);
			}
			S1.print(std::cout);
			continue;
		}
		if (rc == 2) {
			std::cout << "Input new size by X and Y" << std::endl;
			Cordinate c = input_c();
			S1.reset_Size(c);
			S1.print(std::cout);
			continue;
		}
		if (rc == 3) {
			std::cout << "Input cordinates of object" << std::endl;
			Cordinate c = input_c();
			cell = S1.return_object(c);
			std::cout << "Type: " << cell->get_type() << std::endl;
		}
		if (rc == 4) {
			S1.print(std::cout);
			continue;
		}
		if (cell->get_type() == 0 || cell->get_type() == 1) {
			while (rc = dialog(msgs_cell, NMsgs_cell)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
				}
			}
		}
		if (cell->get_type() == 2) {
			platform = dynamic_cast<Platform*>(cell);
			while (rc = dialog(msgs_platform, NMsgs_platform)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
					continue;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
					continue;
				}
				if (rc == 3) {
					std::cout << "Type: " << platform->get_pltype() << std::endl;
					continue;
				}
				if (rc == 4) {
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					bool p = true;
					platform->add_module(mt, les, lec, p, n, nms, r);
					continue;
				}
				if (rc == 5) {
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					if (platform->get_module_is(mt, les, lec, n, nms, r).x == 1) {
						std::cout << "Found!" << std::endl;
					}
					else {
						std::cout << " Not found!" << std::endl;
					}
					continue;
				}
				if (rc == 6) {
					platform = dynamic_cast<Platform*>(cell);
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					platform->delete_module(mt, les, lec, n, nms, r);
					continue;
				}
				if (rc == 7) {/*
					std::cout << "Input index of module" << std::endl;
					int i;
					while (getNum(i) < 0)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}*/
					platform = dynamic_cast<Platform*>(cell);
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					Cordinate c = platform->get_module_is(mt, les, lec, n, nms, r);
					if (c.x == 1) {
						module = platform->return_module(c.y);
					}
					else {
						std::cout << "You're wrong. Repeat please" << std::endl;
						continue;
					}
				}
				if (rc == 8) {
					platform = dynamic_cast<Platform*>(cell);
					if (platform->get_pltype() == 2) {
						Mobile_Platform* mob_pl = dynamic_cast<Mobile_Platform*>(platform);
						std::cout << "Input where enemy should move : 4862" << std::endl;
						int r;
						while (getNum(r) < 0 && r != 4 && r != 6 && r != 2 && r != 8)
						{
							std::cout << "You're wrong. Repeat please" << std::endl;
						}
						std::cout << std::endl;
						mob_pl->Move(r, S1);
						S1.print(std::cout);
					}
					else {
						std::cout << "Static platform can't moves" << std::endl;
					}
					continue;
				}
				if (module->get_mtype() == 1) {
					Network* network = dynamic_cast<Network*>(module);
					while (rc = dialog(msgs_network, NMsgs_network)) {
						if (rc == 1) {
							network->get_Partners(S1,*platform);
							network->put_active_Partners();
							network->put_all_Partners();
						}
						if (rc == 2) {
							std::cout << "Input cordinates of connect-pl" << std::endl;
							Cordinate c = c = input_c();
							network->ask_Partners(c, S1, *platform);
							network->put_active_Partners();
							network->put_all_Partners();
						}
						if (rc == 3) {
							network->take_info(*platform);
							platform->put_objects_info();
						}
					}
				}
				if (module->get_mtype() == 2) {
					while (rc = dialog(msgs_sensor, NMsgs_sensor)) {
						if (rc == 1) {
							Sensor* sensor = dynamic_cast<Sensor*>(module);
							sensor->Get_info(S1, *platform);
							platform->put_objects_info();
						}
					}
				}
				if (module->get_mtype() == 3) {
					Weapon* weapon = dynamic_cast<Weapon*>(module);
					while (rc = dialog(msgs_weapon, NMsgs_weapon)) {
						if (rc == 1) {
							weapon->Kill(*platform, S1);
						}
						if (rc == 3) {
							weapon->outCharge();
						}
						if (rc == 2) {
							weapon->inCharge();
						}
					}
				}
			}
		}
		if (cell->get_type() == 3) {
			while (rc = dialog(msgs_enemy, NMsgs_enemy)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
				}
				if (rc == 3) {
					Enemy* enemy = dynamic_cast<Enemy*>(cell);
					std::cout << "Input where enemy should move : 4862" << std::endl;
					int r;
					while (getNum(r) < 0 && r != 4 && r != 6 && r != 2 && r != 8)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << std::endl;
					if (!(enemy = enemy->move(r, S1)))
						std::cout << "This cell is busy" << std::endl << std::endl;
					else
						cell = enemy;
					S1.print(std::cout);
				}
				if (rc == 4) {
					Enemy* enemy;
					enemy = dynamic_cast<Enemy*>(cell);
					enemy->destruction();
					S1.print(std::cout);
					break;
				}
			}
		}
	}
	return 1;
}