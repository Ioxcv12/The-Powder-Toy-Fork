#include "simulation/ElementCommon.h"
void Element::Element_COAL()
{
	Identifier = "DEFAULT_PT_APCP";
	Name = "APCP";
	Colour = 0x222222_rgb;
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.0f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;
	PhotonReflectWavelengths = 0x00000000;

	Weight = 100;

	HeatConduct = 200;
	Description = "APCP";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	DefaultProperties.life = 110;
	DefaultProperties.tmp = 50;
}

int Element_APCP_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life<=0) {
		sim->create_part(i, x, y, PT_FIRE);
		return 1;
	} else if (parts[i].life < 100) {
		parts[i].life--;
		sim->create_part(-1, x + sim->rng.between(-1, 1), y + sim->rng.between(-1, 1), PT_FIRE);
	}
	if (parts[i].type == PT_APCP)
	{
		if ((sim->pv[y/CELL][x/CELL] > 4.3f)&&parts[i].tmp>40)
			parts[i].tmp=39;
		else if (parts[i].tmp<40&&parts[i].tmp>0)
			parts[i].tmp--;
		else if (parts[i].tmp<=0) {
			sim->part_change_type(i, x, y, PT_BCOL);
			return 1;
		}
	}
	if(parts[i].temp > parts[i].tmp2)
		parts[i].tmp2 = int(parts[i].temp);
	return 0;
}
