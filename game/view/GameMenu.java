package view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameMenu {
    ImageIcon back;
    JButton backButton;
    JButton restartButton;
    JLabel scoreLabel;
    JLabel timerLabel;
    JDialog jDialog;

    public GameMenu() {
        backButton = new JButton("Back");
        backButton.setBounds(10, 10, 180, 40);
        backButton.setFont(Window.miniButtonFont);
        backButton.setForeground(Window.buttonFontColor);
        backButton.setBackground(Window.buttonBackground);
        backButton.setHorizontalAlignment(JLabel.CENTER);
        backButton.setOpaque(false);

        restartButton = new JButton("Restart");
        restartButton.setBounds(10, 50, 180, 40);
        restartButton.setFont(Window.miniButtonFont);
        restartButton.setForeground(Window.levelFontColor);
        restartButton.setBackground(Window.background);
        restartButton.setHorizontalAlignment(JLabel.CENTER);
        restartButton.setOpaque(false);


        back = new ImageIcon("C:\\Users\\nedoletoff\\IdeaProjects\\game\\images/game_image.jpg");


        timerLabel = new JLabel("Timer: 0");
        timerLabel.setBounds(Window.WIDTH - 150, 10, 150, 25);
        timerLabel.setFont(Window.miniButtonFont);
        timerLabel.setForeground(Window.levelFontColor);
        timerLabel.setOpaque(false);

        scoreLabel = new JLabel("Score: 0");
        scoreLabel.setBounds(Window.WIDTH - 150, 35, 150, 25);
        scoreLabel.setFont(Window.miniButtonFont);
        scoreLabel.setForeground(Window.levelFontColor);
        scoreLabel.setOpaque(false);
    }

    public ImageIcon getBack() {
        return back;
    }

    public JButton getBackButton() {
        return backButton;
    }

    public JButton getRestartButton() {
        return restartButton;
    }

    public JLabel getScoreLabel() {
        return scoreLabel;
    }

    public JLabel getTimerLabel() {
        return timerLabel;
    }

    public void setTimer(int time) {
        timerLabel.setText("Timer: " + time);
    }

    public int getTimer() {
        return Integer.parseInt(timerLabel.getText().split(": ")[1]);
    }

    public void setScore(int score) {
        scoreLabel.setText("Score: " + score);
    }

    public int getScore() {
        return Integer.parseInt(scoreLabel.getText().split(": ")[1]);
    }

    public JDialog getEndGameDialog(ActionListener actionListener, JFrame frame) {
        jDialog = new JDialog(frame);

        jDialog.setTitle("End Game");
        jDialog.setIconImage(new ImageIcon("C:\\Users\\nedoletoff\\IdeaProjects\\game\\images\\circle.png").getImage());
        jDialog.setBounds(Window.WIDTH / 2 - 400, Window.HEIGHT / 2 - 250, 800, 500);
        jDialog.setBackground(Window.background);
        jDialog.setFont(Window.levelFont);

        JLabel text = new JLabel("Results");
        text.setFont(Window.dialogFont);
        text.setSize(140, 120);
        text.setFont(Window.levelFont);
        text.setHorizontalAlignment(SwingConstants.CENTER);

        JPanel panel = new JPanel();
        GridLayout grid = new GridLayout(3, 3);
        panel.setLayout(grid);

        JButton back = new JButton("Back to menu");
        back.setSize(120, 120);
        back.addActionListener(e -> {
            jDialog.setVisible(false);
            actionListener.actionPerformed(new
                ActionEvent(e.getSource(), e.getID(), "Back"));
        });

        JButton choose = new JButton("Chose level");
        choose.setSize(120, 120);
        choose.addActionListener(e -> {
            jDialog.setVisible(false);
            actionListener.actionPerformed(new
                    ActionEvent(e.getSource(), 12, "Go to level menu"));
        });
        JButton restart = new JButton("restart");
        restart.setSize(120, 120);
        restart.addActionListener(e -> {
            jDialog.setVisible(false);
            actionListener.actionPerformed(new ActionEvent(e.getSource(), 11, "Restart"));
        });

        JLabel score = new JLabel("Score : " + getScore());
        score.setSize(140, 120);
        score.setFont(Window.levelFont);
        score.setHorizontalAlignment(SwingConstants.CENTER);
        JLabel timer = new JLabel("Timer : " + getTimer());
        timer.setSize(140, 120);
        timer.setFont(Window.levelFont);
        timer.setHorizontalAlignment(SwingConstants.CENTER);


        panel.add(new JLabel());
        panel.add(text);
        panel.add(new JLabel());
        panel.add(score);
        panel.add(new JLabel());
        panel.add(timer);
        panel.add(back);
        panel.add(restart);
        panel.add(choose);
        jDialog.add(panel);
        return jDialog;
    }
}

