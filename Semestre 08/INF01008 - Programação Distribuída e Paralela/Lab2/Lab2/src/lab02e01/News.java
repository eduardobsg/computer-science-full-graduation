package lab02e01;

import java.io.Serializable;
import java.rmi.Remote;
import java.util.Date;

/**
 *
 * @author fkrahe
 */
public class News implements INews, Remote, Serializable {

    private Date date;
    private String text;

    public News(Date date, String text) {
        this.date = date;
        this.text = text;
    }

    @Override
    public void show() {
        System.out.println(text);
    }

    public Date getDate() {
        return date;
    }

    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        return "News{" + "date=" + date + ", text=" + text + '}';
    }
}
