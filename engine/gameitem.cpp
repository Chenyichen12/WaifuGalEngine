#include "gameitem.h"
namespace GalEngine {

Sentence::Sentence(const QString &text, const QString &who)
    : text(text), who(who) {}

Sentence::Sentence() {
    text = "";
    who = "";
}

Sentence Sentence::say(const QString &text) const {
    auto result = *this;
    result.text = text;
    return result;
}

Sentence Sentence::by(const QString &who) const {
    auto result = *this;
    result.who = who;
    return result;
}

Sentence Sentence::show(const QString &url) const {
    auto result = *this;
    result.imageUrl = url;
    return result;
}

CharacterTransform CharacterTransform::move(qreal x, qreal y) const{
    auto result = *this;
    result.pos.setX(x);
    result.pos.setY(y);
    return result;
}
CharacterTransform CharacterTransform::rotate(qreal angle) const{
    auto result = *this;
    result.angle = angle;
    return result;
}
CharacterTransform CharacterTransform::zoom(qreal scale) const{
    auto result = *this;
    result.scale = scale;
    return result;
}
CharacterTransform CharacterTransform::fade(qreal opacity) const{
    auto result = *this;
    result.opacity = opacity;
    return result;
}


Character::Character(const QString &url, const CharacterTransform &t)
    : imageUrl(url), transform(t) {}
} // namespace GalEngine