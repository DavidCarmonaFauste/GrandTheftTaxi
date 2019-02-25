#include "Resources.h"

const double Resources::physicsScalingFactor = 0.2;

vector<Resources::VehicleInfo> Resources::vehicles_{
	{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 50, 100}
};

vector<Resources::SoundInfo> Resources::sounds_{
	{DefaultSoundId, "../Assets/sounds/default.wav"}
};

vector<Resources::MusicInfo> Resources::music_{
	{DefaultMusicId, "../Assets/sounds/default.wav"}
};
