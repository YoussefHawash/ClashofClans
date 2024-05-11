#include "player.h"
#include "gamescene.h"
extern GameScene *gamescene;
QTimer* Player::movetime = new QTimer;

Player::Player(int x, int y, int hp, int s)
    : posx(x)
    , posy(y)
    , speed(s)
{
    h = new health(posx, posy, pixmap().width(), hp);
    setPos(x,y);
    startmove();
}
void Player::startmove()
{

    movetime->start(100);
}

void Player::stopmove()
{
    movetime->stop();
}
health *Player::gethealth()
{
    return h;
}
void Player::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(0.8);
    if (h != nullptr)
        h->show();
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void Player::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(1);
    if (h != nullptr)
        h->hide();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}
vector<Nodes> Player::Dijekstra(const Nodes &start, const Nodes &goal)
{
    int height = gamescene->getmap()->size();
    int width = gamescene->getmap()[0].size();

    // Initialize the cost 2x2 matrix with really high values except for the start position
    vector<vector<float>> cost(height, vector<float>(width, 9999999));
    cost[start.x][start.y] = 0;

    // Priority queue to manage exploration based on the lowest cost first
    priority_queue<pair<float, Nodes>, vector<pair<float, Nodes>>, CostComparator> queue;
    queue.push({0, start});

    // Initialize the parent matrix to reconstruct the path later
    vector<vector<Nodes>> previous(height, vector<Nodes>(width, {-1, -1, 0}));

    // Define possible movement directions: down, up, right, left
    vector<pair<int, int>> directions
        = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    // Loop over the priority queue until it's empty
    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();
        Nodes p = current.second;

        // Stop if we reached the goal
        if (p.x == goal.x && p.y == goal.y)
            break;

        // Explore each possible direction
        for (auto &dir : directions) {
            int nx = p.x + dir.first;
            int ny = p.y + dir.second;

            // Check if the new position is within bounds
            if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
                float newCost = cost[p.x][p.y]
                                + (*gamescene->getmap())[nx][ny]
                                      ->weight; // Assuming cost to move is 1, update if it's different
                if (newCost < cost[nx][ny]) {
                    cost[nx][ny] = newCost;
                    previous[nx][ny] = p; // Record the parent Nodes to reconstruct the path later
                    queue.push(
                        {newCost, {nx, ny, 0}}); // Push the new position to the priority queue
                }
            }
        }
    }

    vector<Nodes> path;
    Nodes step = goal;

    while (!(step.x == start.x && step.y == start.y)) {
        path.push_back(step);
        step = previous[step.x][step.y]; // Move to the parent of the current Nodes
    }

    path.push_back(start); // Add the start Nodes at the end

    // Reverse the path to be from start to goal
    reverse(path.begin(), path.end());
    for (auto &itr : path) {
        qDebug() << itr.x << " " << itr.y;
    }
    return path;
};
