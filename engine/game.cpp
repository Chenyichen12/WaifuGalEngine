#include "game.h"
#include "choiceview.h"
#include "galaction.h"
#include "stage.h"
#include "textbar.h"
#include <QSequentialAnimationGroup>

namespace GalEngine {

GalEngineView::TextBar *Game::textBar() const { return textbar; }
GalEngineView::Stage *Game::stage() const { return stage_; }
GalEngineView::ChoiceView *Game::choiceView() const { return choice_view_; }
Game::Game(QQuickItem *parent) : QQuickItem(parent) {
  textbar = new GalEngineView::TextBar(this);
  stage_ = new GalEngineView::Stage(this);
  choice_view_ = new GalEngineView::ChoiceView(this);
  connect(choice_view_, &GalEngineView::ChoiceView::choose, this,
          &Game::onChoice);
}
Game::~Game() {
  for (auto action : actions_) {
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
  if (action->label() != "") {
    label_table_.insert(action->label(), action->index_);
  }
  actions_.append(action);
  return *this;
}

void Game::moveNext() {
  if (currentActionIndex >= actions_.size() - 1) {
    return;
  }
  do {
    currentActionIndex++;
    actions_[currentActionIndex]->execute(this);
  } while (currentActionIndex < actions_.size() &&
           !actions_[currentActionIndex]->clog());
}

void Game::moveTo(qsizetype index) {
  Q_ASSERT(index >= 0 && index < actions_.size());
  currentActionIndex = index;
  moveNext();
}

void Game::moveTo(const QString &label) {
  Q_ASSERT(label_table_.contains(label));
  moveTo(label_table_[label]);
}

void Game::onChoice(int index) {
  auto label = choice_view_->labels()[index];
  choice_view_->closeAndClear();
  moveTo(label);
}

void Game::showChoices(const QStringList &choices, const QStringList &label) {
  Q_ASSERT(choices.size() == label.size());
  for (qsizetype i = 0; i < choices.size(); i++) {
    choice_view_->addChoice(choices[i], label[i]);
  }
}
} // namespace GalEngine