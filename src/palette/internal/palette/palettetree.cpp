/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "palettetree.h"

#include <QBuffer>

#include "engraving/io/xml.h"

using namespace mu::palette;

void PaletteTree::insert(size_t idx, PalettePanelPtr palette)
{
    palettes.emplace(palettes.begin() + idx, palette);
}

void PaletteTree::append(PalettePanelPtr palette)
{
    palettes.emplace_back(palette);
}

bool PaletteTree::read(Ms::XmlReader& e)
{
    while (e.readNextStartElement()) {
        const QStringRef tag(e.name());
        if (tag == "Palette") {
            PalettePanelPtr p = std::make_shared<PalettePanel>();
            p->read(e);
            palettes.push_back(p);
        } else {
            e.unknown();
        }
    }

    return true;
}

void PaletteTree::write(Ms::XmlWriter& xml) const
{
    xml.stag("PaletteBox"); // for compatibility with old palettes file format

    for (PalettePanelPtr palette : palettes) {
        palette->write(xml);
    }

    xml.etag();
}

void PaletteTree::retranslate()
{
    for (PalettePanelPtr palette : palettes) {
        palette->retranslate();
    }
}
