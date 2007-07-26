/*
 * Stellarium
 * Copyright (C) 2006 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef LANDSCAPEMGR_H_
#define LANDSCAPEMGR_H_

#include "StelModule.hpp"
#include "StelUtils.hpp"

class Landscape;
class Atmosphere;
class Cardinals;

//! @brief Class which manage all the rendering a the level of the observer's surrounding.
//!
//! This includes landscape textures, fog, atmosphere and cardinal points
//! I decided to put all these elements together in a single class because there are 
//! inherently linked, especially when we start moving the observer in altitude
class LandscapeMgr : public StelModule
{
public:
	LandscapeMgr();
	virtual ~LandscapeMgr();
	
	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	virtual void init(const InitParser& conf, LoadingBar& lb);
	virtual string getModuleID() const {return "landscape";}
	virtual double draw(Projector *prj, const Navigator *nav, ToneReproducer *eye);
	virtual void update(double deltaTime);
	virtual void updateI18n();
	virtual void updateSkyCulture(LoadingBar& lb) {;}
	virtual void setColorScheme(const InitParser& conf, const std::string& section);
	virtual double getCallOrder(StelModuleActionName actionName) const;
	
	///////////////////////////////////////////////////////////////////////////
	// Method specific to the landscape manager
	Landscape* create_from_file(const string& landscape_file, const string& section_name);
	Landscape* create_from_hash(map<string, string> & param);
	
	//! retrieve a list of the available landscape IDs separated by the \n character
	//! the ID in this context is the name of the directory in which the landscape
	//! exists, i.e. .../landscapes/ID/...
	string getLandscapeNames();
	
	//! convert the name of a landscape (from the name field in the ini file)
	//! to the ID for the landscape
	string nameToKey(const string& name);

	///////////////////////////////////////////////////////////////////////////////////////
	// Set and gets
	const string& getLandscapeId() {return landscapeSectionName;}
	
	//! Set the landscape
	bool setLandscape(const string& new_landscape_name);

	//! Load a landscape based on a hash of parameters mirroring the landscape.ini file
	//! and make it the current landscape
	bool loadLandscape(map<string, string>& param);
	
	//! Set flag for displaying Landscape
	void setFlagLandscape(bool b);
	//! Get flag for displaying Landscape
	bool getFlagLandscape(void) const;

	//! Set flag for displaying Fog
	void setFlagFog(bool b);
	//! Get flag for displaying Fog
	bool getFlagFog(void) const;

	//! Return the real name of the current landscape
	wstring getLandscapeName(void);
	//! Return the author name of the current landscape
	wstring getLandscapeAuthorName(void);
	//! Return the description of the current landscape
	wstring getLandscapeDescription(void);
	//! Return the translated name of the planet where the current landscape is from
	wstring getLandscapePlanetName(void);
	//! Return a wstring with the longitude, latitude and altitude of the current landscape
	wstring getLandscapeLocationDescription(void);

	bool getFlagLandscapeSetsLocation(void) const {return flagLandscapeSetsLocation;}
	void setFlagLandscapeSetsLocation(bool b) {flagLandscapeSetsLocation=b;}

	//! Set flag for displaying Cardinals Points
	void setFlagCardinalsPoints(bool b);
	//! Get flag for displaying Cardinals Points
	bool getFlagCardinalsPoints(void) const;

	//! Set Cardinals Points color
	void setColorCardinalPoints(const Vec3f& v);
	//! Get Cardinals Points color
	Vec3f getColorCardinalPoints(void) const;
	
	///////////////////////////////////////////////////////////////////////////////////////
	// Atmosphere
	//! Set flag for displaying Atmosphere
	void setFlagAtmosphere(bool b);
	//! Get flag for displaying Atmosphere
	bool getFlagAtmosphere(void) const;

	//! Set atmosphere fade duration in s
	void setAtmosphereFadeDuration(float f);
	//! Get atmosphere fade duration in s
	float getAtmosphereFadeDuration(void) const;

	//! Set light pollution luminance level
	void setAtmosphereLightPollutionLuminance(float f);
	//! Get light pollution luminance level
	float getAtmosphereLightPollutionLuminance(void) const;
	
	//! Return the global landscape luminance, for beeing used e.g for setting eye adaptation
	float getLuminance(void);
	
	//! Return a map of landscape name to landscape ID (directory name)
	std::map<std::string,std::string> getNameToDirMap(void);

private:
	Atmosphere* atmosphere;			// Atmosphere
	Cardinals* cardinals_points;		// Cardinals points
	Landscape* landscape;				// The landscape ie the fog, the ground and "decor"
	
	// Define whether the location is set by the landscape
	bool flagLandscapeSetsLocation;
	
	std::string landscapeSectionName;
};

#endif /*LANDSCAPEMGR_H_*/
