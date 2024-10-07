#include "game.h"
#include "galaction.h"
#include "stage.h"
#include "textbar.h"
#include <QSequentialAnimationGroup>

namespace GalEngine {

GalEngineView::TextBar *Game::textBar() const { return textbar; }
GalEngineView::Stage *Game::stage() const { return stage_; }
Game::Game(QQuickItem *parent) : QQuickItem(parent) {
  textbar = new GalEngineView::TextBar(this);
  stage_ = new GalEngineView::Stage(this);
}
Game::~Game(){
  for(auto action: actions_){
    delete action;
  }
  actions_.clear();
}
void Game::saying(const Sentence &s, int optionFlag) {
  textbar->setText(s.text);
  if (s.who != "") {
    textbar->setSayingName(s.who);
  }
}

void Game::show(const Character &c, int optionFlag) {
  Q_UNUSED(optionFlag)
  stage_->addCharacter(c);
}

void Game::startTransform(const QString &name,
                          const CharacterTransform &start) {
  stage_->startTransform(name, start);
}

void Game::startTransform(const QString &nameUrl) {
  stage_->startTransform(nameUrl, std::nullopt);
}
void Game::addTransform(const QString &target, const CharacterTransform &t,
                        qreal time, int optionFlag) {
  stage_->addTransform(target, t, time, optionFlag);
}
void Game::finishTransform() { stage_->finishTransform(); }

Game &Game::operator<<(GalAction *action) {
  action->index_ = actions_.size();
  actions_.append(action);
  return *this;
}

void Game::moveNext() {
  if(currentActionIndex >= actions_.size()){
    return;
  }
  do {
    actions_[currentActionIndex]->execute(this);
    currentActionIndex++;
  } while (currentActionIndex < actions_.size() &&
           !actions_[currentActionIndex]->clog());
}
} // namespace GalEngine