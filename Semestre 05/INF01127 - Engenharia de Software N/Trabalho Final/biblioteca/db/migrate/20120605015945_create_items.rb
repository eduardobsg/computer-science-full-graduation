class CreateItems < ActiveRecord::Migration
  def self.up
    create_table :items do |t|
      t.string :nome
      t.text :autor
      t.string :assunto
      t.references :itemTipo

      t.timestamps
    end
  end

  def self.down
    drop_table :items
  end
end
