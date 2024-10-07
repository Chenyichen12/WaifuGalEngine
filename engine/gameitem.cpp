#include "gameitem.h"
namespace GalEngine {

Sentence::Sentence(const QString &text, const QString &who)
    : text(text), who(who) {}

Character::Character(const QString &url, const CharacterTransform &t)
    : imageUrl(url), transform(t) {}
} // namespace GalEngine