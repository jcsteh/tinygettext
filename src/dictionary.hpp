//  $Id$
//
//  tinygettext - A gettext replacement that works directly on .po files
//  Copyright (C) 2006 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_DICTIONARY_HPP
#define HEADER_DICTIONARY_HPP

#include <map>
#include <vector>
#include <string>
#include "language.hpp"

namespace tinygettext {

/** A simple dictionary class that mimics gettext() behaviour. Each
    Dictionary only works for a single language, for managing multiple
    languages and .po files at once use the DictionaryManager. */
class Dictionary
{
private:
  typedef std::map<std::string, std::vector<std::string> > Entries;
  Entries entries;

  typedef std::map<std::string, Entries> CtxtEntries;
  CtxtEntries ctxt_entries;

  std::string charset;
  PluralForms plural_forms;

  std::string translate(const Entries& dict, const std::string& msgid);
  std::string translate_plural(const Entries& dict, const std::string& msgid, const std::string& msgidplural, int num);

public:
  /** */
  Dictionary(const std::string& charset = "UTF-8");

  /** Return the charset used for this dictionary */
  std::string get_charset() const;

  void set_plural_forms(const PluralForms&);
  PluralForms get_plural_forms() const;

  /** Translate the string \a msgid. */
  std::string translate(const std::string& msgid);
  const char* translate(const char* msgid);

  /** Translate the string \a msgid to its correct plural form, based
      on the number of items given by \a num. \a msgid_plural is \a msgid in
      plural form. */
  std::string translate_plural(const std::string& msgid, const std::string& msgidplural, int num);
  const char* translate_plural(const char* msgid, const char* msgidplural, int num);

  /** Translate the string \a msgid that is in context \a msgctx. A
      context is a way to disambiguate msgids that contain the same
      letters, but different meaning. For example "exit" might mean to
      quit doing something or it might refer to a door that leads
      outside (i.e. 'Ausgang' vs 'Beenden' in german) */
  std::string translate_ctxt(const std::string& msgctxt, const std::string& msgid);
  const char* translate_ctxt(const char* msgctxt, const char* msgid);

  std::string translate_ctxt_plural(const std::string& msgctxt, const std::string& msgid, const std::string& msgidplural, int num);
  const char* translate_ctxt_plural(const char* msgctxt, const char* msgid, const char* msgidplural, int num);

  /** Add a translation from \a msgid to \a msgstr to the dictionary,
      where \a msgid is the singular form of the message, msgid_plural the
      plural form and msgstrs a table of translations. The right
      translation will be calculated based on the \a num argument to
      translate(). */
  void add_translation(const std::string& msgid, const std::string& msgid_plural,
                       const std::vector<std::string>& msgstrs);
  void add_translation(const std::string& msgctxt, 
                       const std::string& msgid, const std::string& msgid_plural,
                       const std::vector<std::string>& msgstrs);

  /** Add a translation from \a msgid to \a msgstr to the
      dictionary */
  void add_translation(const std::string& msgid, const std::string& msgstr);
  void add_translation(const std::string& msgctxt, const std::string& msgid, const std::string& msgstr);
};

} // namespace tinygettext

#endif

/* EOF */
