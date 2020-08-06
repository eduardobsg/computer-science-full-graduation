class CreateItemTipos < ActiveRecord::Migration
  def self.up
    create_table :item_tipos do |t|
      t.string :nome

      t.timestamps
    end
  end

  def self.down
    drop_table :item_tipos
  end
end
