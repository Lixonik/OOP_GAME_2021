all: app.exe

app.exe: dude.o Model.o View.o Presenter.o Controller.o Logger.o ConsoleLoggingListener.o FileLoggingListener.o Field.o Cell.o Random.o Player.o Zombie.o Goblin.o Orc.o MedKit.o Sword.o Armor.o 
	g++ dude.o Model.o View.o Presenter.o Controller.o Logger.o ConsoleLoggingListener.o FileLoggingListener.o Field.o Cell.o Random.o Player.o Zombie.o Goblin.o Orc.o MedKit.o Sword.o Armor.o -o app && make -f Makefile clean

dude.o: dude.cpp .\Presenter\Presenter.h .\View\View.h .\Rules\Rule_1.h
	g++ -c dude.cpp

Model.o: .\Model\Model.cpp .\Model\Model.h .\Dependencies\json\nlohmann\json.hpp
	g++ -c .\Model\Model.cpp

View.o: .\View\View.cpp .\View\View.h
	g++ -c .\View\View.cpp

Presenter.o: .\Presenter\Presenter.cpp .\Presenter\Presenter.h
	g++ -c .\Presenter\Presenter.cpp

Controller.o: .\Controller\Controller.cpp .\Controller\Controller.h
	g++ -c .\Controller\Controller.cpp

Logger.o: .\Logger\Logger.cpp .\Logger\Logger.h .\LoggingListener\LoggingListener.h
	g++ -c .\Logger\Logger.cpp

ConsoleLoggingListener.o: .\ConsoleLoggingListener\ConsoleLoggingListener.cpp .\ConsoleLoggingListener\ConsoleLoggingListener.h
	g++ -c .\ConsoleLoggingListener\ConsoleLoggingListener.cpp

FileLoggingListener.o: .\FileLoggingListener\FileLoggingListener.cpp .\FileLoggingListener\FileLoggingListener.h
	g++ -c .\FileLoggingListener\FileLoggingListener.cpp

Field.o: .\Field\Field.cpp .\Field\Field.h
	g++ -c .\Field\Field.cpp

Cell.o: .\Cell\Cell.cpp .\Cell\Cell.h
	g++ -c .\Cell\Cell.cpp

Random.o: .\Random\Random.cpp .\Random\Random.h
	g++ -c .\Random\Random.cpp

Player.o: .\Player\Player.cpp .\Player\Player.h
	g++ -c .\Player\Player.cpp

Zombie.o: .\Zombie\Zombie.cpp .\Zombie\Zombie.h
	g++ -c .\Zombie\Zombie.cpp

Goblin.o: .\Goblin\Goblin.cpp .\Goblin\Goblin.h
	g++ -c .\Goblin\Goblin.cpp

Orc.o: .\Orc\Orc.cpp .\Orc\Orc.h
	g++ -c .\Orc\Orc.cpp

MedKit.o: .\MedKit\MedKit.cpp .\MedKit\MedKit.h
	g++ -c .\MedKit\MedKit.cpp

Sword.o: .\Sword\Sword.cpp .\Sword\Sword.h
	g++ -c .\Sword\Sword.cpp

Armor.o: .\Armor\Armor.cpp .\Armor\Armor.h
	g++ -c .\Armor\Armor.cpp

clean:
	erase *.o
