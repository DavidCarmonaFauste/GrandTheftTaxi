#pragma once

class EstadosEnum
{

	
private:
	enum Estados
	{
		Video_State_,
		MainMenu_State_,
		Juego_State_,
		PauseMenu_State_,
		Victoria_State_,
		GameOver_State_
	};
public:
	Estados getEstados() {
		return Estados;
	}

};

