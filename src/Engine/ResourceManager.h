/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_RESOURCEMANAGER_H
#define FALLTERGEIST_RESOURCEMANAGER_H

// C++ standard includes
#include <list>
#include <string>
#include <map>

// Falltergeist includes

// Third party includes
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{
class Surface;

class ResourceManager
{
protected:
    static std::vector<libfalltergeist::DatFile*> _datFiles;
    static std::map<std::string, libfalltergeist::DatFileItem*> _datFilesItems;
    static std::map<std::string, Surface*> _surfaces;

public:
    ResourceManager();
    ~ResourceManager();
    static libfalltergeist::AafFileType* aafFileType(std::string filename);
    static libfalltergeist::BioFileType* bioFileType(std::string filename);
    static libfalltergeist::DatFileItem* datFileItem(std::string filename);
    static libfalltergeist::FrmFileType* frmFileType(std::string filename);
    static libfalltergeist::FrmFileType* frmFileType(unsigned int FID);
    static libfalltergeist::FonFileType* fonFileType(std::string filename);
    static libfalltergeist::GamFileType* gamFileType(std::string filename);
    static libfalltergeist::GcdFileType* gcdFileType(std::string filename);
    static libfalltergeist::PalFileType* palFileType(std::string filename);
    static libfalltergeist::IntFileType* intFileType(std::string filename);
    static libfalltergeist::IntFileType* intFileType(unsigned int SID);
    static libfalltergeist::LstFileType* lstFileType(std::string filename);
    static libfalltergeist::MapFileType* mapFileType(std::string filename);
    static libfalltergeist::MsgFileType* msgFileType(std::string filename);
    static libfalltergeist::ProFileType* proFileType(std::string filename);
    static libfalltergeist::ProFileType* proFileType(unsigned int PID);
    static libfalltergeist::RixFileType* rixFileType(std::string filename);
    static Surface* surface(std::string filename, int x = 0, int y = 0, unsigned int direction = 0, unsigned int frame = 0);
    static Surface* surface(unsigned int FID, unsigned int direction = 0, unsigned int frame = 0);
    static void extract(std::string path);
    static void unloadResources();
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
