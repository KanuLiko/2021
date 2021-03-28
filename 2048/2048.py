import curses
from itertools import chain
from random import choice


class GameField(object):
    def __init__(self, width=4, height=4, win_value=8):
        self.width = width
        self.height = height
        self.win_value = win_value
        self.highscore = 0
        self.score = 0
        self.moves = {}
        self.moves['Left'] = self.is_move_left
        self.moves['Right'] = self.is_move_right
        self.moves['Down'] = self.is_move_down
        self.moves['Up'] = self.is_move_up

        self.movesDict = {}
        self.movesDict['Left'] = self.move_left
        self.movesDict['Right'] = self.move_right
        self.movesDict['Down'] = self.move_down
        self.movesDict['Up'] = self.move_up

    def reset(self):
        if self.score > self.highscore:
            self.highscore = self.score
        self.score = 0
        # require 1: generate a 4*4 chess board
        self.field = [[0 for j in range(self.width)] for i in range(self.height)]
        self.random_create()
        self.random_create()

    def random_create(self):
        while True:
            i, j = choice(range(self.height)), choice(range(self.width))
            if self.field[i][j] == 0:
                self.field[i][j] = choice([2, 2, 2, 4])
                break

    def draw(self, stdscr):
        def draw_sep():
            stdscr.addstr('+'+"-----+"*self.width+'\n')

        def draw_one_row(row):
            stdscr.addstr("".join('|{:^5}'.format(num) if num != 0 else "|  " for num in row)+'|'+'\n')

        stdscr.clear()
        stdscr.addstr("2048".center(50, '-')+'\n')
        stdscr.addstr("当前分数:" + str(self.score)+'\n')
        if self.highscore != 0:
            stdscr.addstr("最高分:"+str(self.highscore)+'\n')
        for row in self.field:
            draw_sep()
            draw_one_row(row)
        draw_sep()

        if self.is_win():
            stdscr.addstr("胜利！！！"+'\n')
        if self.is_gameover():
            stdscr.addstr("游戏结束！！！"+'\n')
        stdscr.addstr("游戏帮助: 上下左右键(R)Restart Q(Quit)")

    def is_win(self):
        return max(chain(*self.field)) >= self.win_value

    def is_gameover(self):
        return not any([self.move_is_possible(direction) for direction in self.moves])

    @staticmethod
    def invert(field):
        return [row[::-1] for row in field]

    @staticmethod
    def transpose(field):
        return [list(row) for row in zip(*field)]

    @staticmethod
    def is_row_change(row):
        def is_change(i):
            if row[i] == 0 and row[i+1] != 0:
                return True
            if row[i] != 0 and row[i] == row[i+1]:
                return True
            return False
        return any([is_change(index) for index in range(len(row)-1)])

    def is_move_left(self, field):
        return any([self.is_row_change(row) for row in field])

    def is_move_right(self, field):
        field = self.invert(field)
        print(field)
        return self.is_move_left(field)

    def is_move_up(self, field):
        field = self.transpose(field)
        return self.is_move_left(field=field)

    def is_move_down(self, field):
        field = self.transpose(field)
        return self.is_move_right(field)

    def move_is_possible(self, direction):
        if direction in self.moves:
            return self.moves[direction](self.field)
        else:
            return False

    @staticmethod
    def tight(row):
        return sorted(row, key=lambda x: 1 if x == 0 else 0)

    def merge(self, row):
        for i in range(len(row)-1):
            if row[i] == row[i+1]:
                row[i] *= 2
                row[i+1] = 0
        self.score += row[i]
        return row

    def move_row_left(self, row):
        return self.tight(self.merge(self.tight(row)))

    def move_left(self, field):
        return [self.move_row_left(row) for row in field]

    def move_right(self, field):
        field = self.invert(field)
        return self.invert([self.move_row_left(row) for row in field])

    def move_up(self, field):
        return self.transpose([self.move_row_left(row) for row in self.field])

    def move_down(self, field):
        return self.invert(self.transpose([self.move_row_left(row) for row in self.invert(self.transpose(field=field))]))

    def move(self, direction):
        if direction in self.movesDict:
            if self.move_is_possible(direction=direction):
                self.field = self.movesDict[direction](self.field)
                self.random_create()
                return True
        else:
            return False


def get_user_action(stdscr):
    action = stdscr.getch()
    if action == curses.KEY_UP:
        return 'Up'
    if action == curses.KEY_DOWN:
        return 'Down'
    if action == curses.KEY_LEFT:
        return 'Left'
    if action == curses.KEY_RIGHT:
        return 'Right'
    if action == ord('r'):
        return 'Restart'
    if action == ord('q'):
        return 'Exit'


def main(stdscr):

    def init():
        game_field.reset()
        game_field.draw(stdscr=stdscr)
        return 'Game'

    def game():
        game_field.draw(stdscr=stdscr)
        action = get_user_action(stdscr=stdscr)
        if action == 'Restart':
            return 'Init'
        if action == 'Exit':
            return 'Exit'
        if game_field.move(action):
            if game_field.is_win():
                return "Win"
            if game_field.is_gameover():
                return "GameOver"
        return "Game"

    def not_game():
        game_field.draw(stdscr=stdscr)
        while True:
            action = get_user_action(stdscr=stdscr)
            if action == "Restart":
                return "Init"
            if action == "Exit":
                return "Exit"

    state_actions = {
        "Init": init,
        "Game": game,
        "Win": not_game,
        "GameOver": not_game
    }

    game_field = GameField()
    state = "Init"

    while state != 'Exit':
        state = state_actions[state]()


curses.wrapper(main)
