package view;

import java.awt.event.ActionEvent;
import java.util.Objects;

public class LevelRedactorPanel extends LevelPanel{

    public LevelRedactorPanel(Window window) {
        super(window);
        jLabel.add(menu.getNewButton());
        menu.getNewButton().addActionListener(e -> this.actionPerformed(new ActionEvent(e.getSource(),
                999, "New level")));
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (Objects.equals(e.getActionCommand(), "Back"))
            mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    e.getID(), "Back to main menu"));
        switch (e.getID()) {
            case (777) -> mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    888, e.getActionCommand()));
            case (999) -> mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    e.getID(), "New level"));
        }
    }
}
