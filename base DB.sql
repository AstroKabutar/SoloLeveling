CREATE TABLE players (
    player_id INT PRIMARY KEY AUTO_INCREMENT,
    player_name VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE levels (
    level INT PRIMARY KEY,
    xp_required INT
);

CREATE TABLE player_progression (
    player_id INT,
    current_level INT,
    current_xp INT,
    FOREIGN KEY (player_id) REFERENCES players(player_id),
    FOREIGN KEY (current_level) REFERENCES levels(level)
);

CREATE TABLE xp_transactions (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    player_id INT,
    xp_gained INT,
    transaction_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (player_id) REFERENCES players(player_id)
);

------------------------------------------------------------- 

INSERT INTO players (player_name) VALUES ('Alice'), ('Bob');

INSERT INTO levels (level, xp_required) VALUES
(1, 0),    -- Level 1 requires 0 XP
(2, 100),  -- Level 2 requires 100 XP
(3, 250),  -- Level 3 requires 250 XP
(4, 500);  -- Level 4 requires 500 XP

INSERT INTO player_progression (player_id, current_level, current_xp) VALUES
(1, 1, 0),  -- Alice starts at level 1 with 0 XP
(2, 1, 0);  -- Bob starts at level 1 with 0 XP

INSERT INTO xp_transactions (player_id, xp_gained) VALUES
(1, 150),  -- Alice gains 150 XP
(2, 50);   -- Bob gains 50 XP

