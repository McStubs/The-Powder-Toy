#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_REPL PT_REPL 160
Element_REPL::Element_REPL()
{
	Identifier = "DEFAULT_PT_REPL";
	Name = "RPEL";
	Colour = PIXPACK(0x99CC00);
	MenuVisible = 1;
	MenuSection = SC_FORCE;
	Enabled = 1;
	
	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f  * CFDS;
	Falldown = 0;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;
	
	Weight = 100;
	
	Temperature = 20.0f+0.0f  +273.15f;
	HeatConduct = 0;
	Description = "Repel or attract particles based on temp value.";
	
	State = ST_NONE;
	Properties = TYPE_SOLID;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_REPL::update;
	
}

//#TPT-Directive ElementHeader Element_REPL static int update(UPDATE_FUNC_ARGS)
int Element_REPL::update(UPDATE_FUNC_ARGS)
 {
	int r, rx, ry, ri;
	for(ri = 0; ri <= 10; ri++)
	{
		rx = (rand()%21)-10;
		ry = (rand()%21)-10;
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y+ry][x+rx];
			if (!r)
				r = sim->photons[y+ry][x+rx];

			if (r && !(sim->elements[r&0xFF].Properties & TYPE_SOLID)){
				parts[r>>8].vx += isign(rx)*((parts[i].temp-273.15)/10.0f);
				parts[r>>8].vy += isign(ry)*((parts[i].temp-273.15)/10.0f);
			}
		}
	}
	return 0;
}


Element_REPL::~Element_REPL() {}
